# Note détaillée — Parsing dans le projet Cub3D

Objet : expliquer étape par étape comment le parsing est implémenté dans ce projet, quels fichiers et fonctions interviennent, ce qu'elles font et pourquoi, comment l'initialisation et le nettoyage sont organisés, et quelles difficultés/pitfalls ont été évitées.

Cette note est écrite en français, structurée et ciblée pour quelqu'un qui connaît la programmation C mais qui ne connaît pas ce code.

## Vue d'ensemble du flux (ordre d'exécution)

1. `main.c` appelle `init_engine(&engine)` pour initialiser l'état.
2. `main` puis vérifie les arguments et appelle `get_file_data(engine, engine->mapinfo.file)` après avoir chargé le fichier via `load_cub_file` (voir plus bas).
3. Le parsing lit d'abord les lignes du fichier (textures et couleurs), puis détecte le début de la section "map" et construit la carte.
4. Après le parsing, le projet valide la carte (`validate_map`) et les textures/couleurs (`validate_textures_and_colors`).
5. L'initialisation MLX et le chargement des textures (`init_mlx`, `init_textures`) suivent.
6. En cas d'erreur ou à la sortie, les fonctions de cleanup (`free_engine`, `clean_exit`, `mlx_platform_cleanup`) libèrent les ressources.

---

## Fichiers examinés

Dossiers/fichiers analysés :
- `src/initializer/` : `init_engine.c`, `init_mlx.c`, `init_textures.c`
- `src/parser/` : `parse_file_content.c`, `parse_config.c`, `parse_colors.c`, `parse_map_layout.c`, `map_utils.c`, `map_validation.c`, `map_walls_validator.c`, `validate_file.c`, `validate_textures.c`
- `src/cleanup/` : `cleanup.c`, `exit_prog.c`, `error_handler.c`, `mlx_linux_platform.c`, `mlx_macos_platform.c`
- `src/debug/` : `debug.c`
- `src/main.c`

Pour chaque fichier ci-dessous : description, fonctions, rôle et pourquoi.

---

## `main.c`
- Rôle : point d'entrée. Ordonne l'initialisation, parsing, initialisation MLX, chargement textures puis boucle principale.
- Fonctions importantes/call flow :
  - `init_engine(&engine)` — met en valeur le contrat : engine vide / champs par défaut.
  - `parse_args` (interne) : appelle `validate_file` et `load_cub_file`, puis `get_file_data` et `validate_map` etc.
  - `init_mlx`, `init_textures`, `render_images`, `register_input_hooks` puis `mlx_loop_hook` et `mlx_loop`.

Pourquoi ici : `main` orchestre. Le parsing est fait avant `init_mlx` et `init_textures`, car on a besoin des chemins de textures et des couleurs avant de créer les images.

---

## Initialisation — `src/initializer/`

Objectif : préparer structures (engine, player, mapinfo, textures) avant parsing et rendu.

### `init_engine.c`
- `init_image(t_image *img)` : met les champs d'une structure image à zéro/NULL. Utile pour éviter d'appeler `mlx_destroy_image` sur des pointeurs non initialisés.
- `init_raycast(t_raycast *ray)` : met les valeurs pour le raycasting à 0.
- `init_map_context(t_map_context *map)` : initialise champs du contexte de la map (fd = -1, taille 0, pointeurs NULL).
- `init_player(t_player *player)` : initialise la structure player à valeurs neutres.
- `init_engine(t_engine *engine)` : appelle les précédentes et initialise les pointeurs/valeurs racines (win, mlx, map = NULL, etc.).

Pourquoi : le parsing remplit plusieurs de ces champs ; les initialiser évite des frees invalides et des comportements indéfinis si parsing échoue.

### `init_mlx.c`
- `init_image_mlx` et `init_texture_image` : wrappers autour des appels MLX pour créer une image et récupérer le buffer.
- `init_mlx(t_engine *engine)` : démarre MLX (`mlx_init`), crée la fenêtre (`mlx_new_window`) et centre la souris si BONUS activé (`mlx_center_mouse`).

Pourquoi : MLX doit être init avant de charger réellement les textures (qui utilisent `mlx_xpm_file_to_image`). Le code garde l'initialisation MLX séparée du parsing.

### `init_textures.c`
- `load_xpm_texture` : charge un fichier XPM avec `init_texture_image`, copie les pixels dans un buffer int * alloué, puis détruit l'image MLX temporaire.
- `init_textures` : réserve l'array `engine->textures` et charge les 4 textures de mur (N/S/E/W) via `load_xpm_texture`.
- `init_texture_info` : initialise la structure `t_texture_info` (chemins NULL, couleurs NULL, taille TEX_SIZE, etc.).

Pourquoi : séparation chargement chemin (parsing) / chargement binaire (MLX). Après la validation des chemins et des couleurs, `init_textures` est appelé pour produire des buffers prêts à l'emploi pour le rendu.

---

## Parsing — `src/parser/` (détaillé)

But global : récupérer depuis le fichier `.cub` :
- les chemins des textures (NO, SO, WE, EA),
- les couleurs plafond et sol (C et F),
- la grille de la map.

Entrée principale : `load_cub_file` puis `get_file_data`.

### 1) Chargement du fichier en mémoire — `parse_file_content.c`
- `count_file_lines(char *path)` : ouvre le fichier, parcourt toutes les lignes avec `get_next_line` pour compter le nombre total de lignes. (nécessaire pour préallouer le tableau `mapinfo.file`).
  - Pourquoi : on préfère lire deux fois (compter -> allouer -> lire) pour simplifier la gestion mémoire plutôt que de réallouer dynamiquement à chaque ligne.
  - Pitfall : `get_next_line` doit être fiable pour ne pas laisser de fuite ; les erreurs d'ouverture sont converties en message via `print_error_msg`.
- `store_file_line(t_engine *data, char *line, int index)` : alloue et copie la ligne dans `data->mapinfo.file[index]`.
- `load_file_lines(t_engine *data)` : itère sur les lignes ouvertes via `data->mapinfo.fd`, appelle `store_file_line` pour chaque ligne et termine par un `NULL` sentinel.
- `load_cub_file(char *path, t_engine *data)` : met tout cela ensemble : compte les lignes, alloue `mapinfo.file`, ouvre le fichier et charge les lignes.

Contrat : après `load_cub_file`, `data->mapinfo.file` est un tableau `char **` où chaque entrée est une ligne terminée par '\0', et le tableau est terminé par `NULL`.

### 2) Parcours de haut en bas — `parse_config.c` (`get_file_data`)
- `get_file_data(t_engine *data, char **file)` : boucle `row` puis `col` et appelle `parse_line_` pour décider quoi faire avec la ligne/position.
  - La stratégie : parcours caractère par caractère pour repérer un identifiant au début d'une ligne (après espaces) :
    - si ça commence par deux lettres alphabétiques (ex: NO, SO, WE, EA) -> `parse_direction_texture`
    - si ça commence par une lettre unique (F ou C) -> `parse_floor_ceiling_color`
    - si ça commence par un chiffre (la map, typiquement '1') -> `parse_map_layout` et ON SORT (SUCCESS)
    - sinon : IGNORE et continue
- `parse_line_` : gère l'analyse de la ligne actuelle (skip espaces puis decide). Renvoie
  - `CONTINUE` : continuer l'itération de colonnes
  - `BREAK` : ligne traitée (passer à la ligne suivante)
  - `SUCCESS` : parsing du bloc map démarré et terminé (on retourne avec succès)
  - `FAILURE` : échec

Pourquoi : lire séquentiellement et détecter la map dès qu'on a une ligne qui commence par digit (typiquement '1') simplifie l'algorithme car la map doit être la dernière section.

### 3) Textures directionnelles — `parse_config.c` et `extract_texture_path`
- `extract_texture_path(char *line, int start)` : saute espaces, cherche la fin du chemin (premier espace/tab), alloue la string du chemin, vérifie qu'il n'y a pas d'extra non attendu après le chemin.
- `parse_direction_texture(t_texture_info *tex, char *line, int index)` : selon l'identifiant (NO, SO, WE, EA) assigne `tex->north/south/etc` si non déjà défini, sinon retourne `ERR`.

Pitfalls traités :
- Validation de la présence d'au moins un espace après l'identifiant.
- Empêcher la duplication (définitions répétées).
- S'assurer qu'il n'y a pas d'autres tokens sur la même ligne après le chemin.

### 4) Couleurs plafond/sol — `parse_colors.c`
- `parse_floor_ceiling_color(data, textures, line, index)`
  - Vérifie qu'il y a un espace après 'F' ou 'C'.
  - Appelle `extract_rgb_from_line(&line[index + 1])`.
- `extract_rgb_from_line` utilise `line_contains_exactly_two_commas`, `ft_split` (séparé par ',') et `parse_rgb_values` pour convertir chaque composant en int.
  - `parse_rgb_value` fait un `ft_strtrim`, vérifie que la chaîne résultante est strictement numérique (`is_strict_digit_str`) et convertit avec `ft_atoi`.
  - Les valeurs sont ensuite validées plus tard par `validate_textures_and_colors` via `validate_rgb_range` (0..255).

Pitfalls traités :
- Validation stricte du format `R,G,B` avec exactement deux virgules.
- Trimming des espaces autour des composants.
- Conversion sécurisée et libérations en cas d'erreur.

### 5) Construction de la map — `parse_map_layout.c`
- Détectée quand `get_file_data` trouve une ligne qui commence par un chiffre (typiquement '1').
- `parse_map_layout` appelle `extract_map_data` :
  - `count_map_height` : compte les lignes de map consécutives (une ligne de map doit commencer par '1' après spaces). Met à jour `mapinfo.index_end_of_map`.
  - `build_map_array` : alloue `mapinfo.height` lignes, pour chaque ligne copie jusqu'au '\n' et pad avec '\0' jusqu'à `mapinfo.width` = `get_max_map_line_length`.
- Après construction, `replace_inner_spaces_with_walls` remplace les espaces internes (non bord) par '1' pour s'assurer que les espaces internes deviennent des murs (empêche des ouvertures dans la map).

Pourquoi : la map est stockée en tableau rectangulaire (padding) afin de simplifier la validation et le raycasting. Le remplacement des espaces internes par des murs est une stratégie conservatrice pour éviter des cellules non définies au milieu.

---

## Validation finale — `validate_*` et `map_validation.c`

### `validate_file.c` (utilisé aussi pour textures XPM)
- Vérifie que le chemin n'est pas un dossier (`is_directory` utilisant `open(..., O_DIRECTORY)`), que le fichier s'ouvre, puis vérifie l'extension (.cub si `cub==true`, .xpm sinon).
- Retourne `SUCCESS` ou `FAILURE` (avec messages d'erreur via `print_error_msg`).

### `validate_textures.c`
- `validate_textures_and_colors` : vérifie la présence des 4 textures et des 2 couleurs, valide que les fichiers existent (`validate_file(false, path)`), valide les valeurs RGB (`validate_rgb_range`) et stocke `hex_floor` / `hex_ceiling`.
- `validate_rgb_range` : garanti 0..255.

### `map_walls_validator.c` & `map_validation.c`
- `validate_map_walls` : vérifie que la première et la dernière ligne sont uniquement des '1' (après espaces) et que chaque ligne intermédiaire se termine par '1'.
- `validate_map_elements` : parcours la map, autorise seulement les caractères `1`, `0`, `NSEW` et vérifie qu'il y a exactement un joueur.
- `init_player_position` : place le joueur au centre de la tuile (x+0.5, y+0.5), remplace le caractère directionnel par '0'.
- `validate_player_enclosure` : vérifie que les cellules autour du joueur ne sont pas des espaces ou hors-limites.
- `validate_map_is_last` : vérifie qu'aucun contenu non-blanc n'existe après la map dans le fichier.

Pourquoi ces validations : elles évitent des crashs lors du raycasting (par exemple accès hors-borne si la map n'est pas fermée), et garantissent l'intégrité des données avant d'initialiser les textures/MLX.

---

## Nettoyage et gestion d'erreurs — `src/cleanup/` et `error_handler.c`

### `error_handler.c`
- `print_error_msg` / `print_error_msg_int` : centralisent l'affichage d'erreur sur stderr et retournent un code.

### `cleanup.c`
- `free_2d_array(void **array)` : libère un tableau NULL-terminé.
- `free_texture_info(t_texture_info *textures)` : libère les chaînes allouées.
- `free_map_context(t_engine *engine)` : ferme fd si ouvert et libère `mapinfo.file` et `engine->map`.
- `free_engine` : libère `textures`, `texture_pixels`, appelle `free_texture_info` et `free_map_context`.

### `exit_prog.c`
- `clean_exit` : détruit la fenêtre et images MLX si présentes, appelle `mlx_platform_cleanup` (Linux / macOS spécifique), libère `engine` et `exit(code)`.
- `quit_cub3d` : wrapper retournant 0.

### `mlx_*_platform.c`
- `mlx_platform_cleanup` (Linux) : `mlx_destroy_display(mlx)`, `mlx_loop_end(mlx)`, `free(mlx)`.
- `mlx_center_mouse`, `mlx_move_mouse` wrappers autour des appels MLX spécialisés selon OS.

Pourquoi : centraliser le cleanup évite les fuites et s'assure que même lors d'erreurs pendant le parsing on peut free proprement.

---

## Fonctions de debug
- `src/debug/debug.c` fournit des helpers (`debug_display_mapinfo`, `debug_display_player`, `debug_display_minimap`) pour afficher l'état interne. Très utile lors du développement du parsing pour imprimer la map et vérifier les valeurs.

---

## Contrats, entrées/sorties et erreurs communes

- Entrée principale pour le parsing : `load_cub_file(path, engine)` puis `get_file_data(engine, engine->mapinfo.file)`.
- Contrat pour `get_file_data` : remplit `engine->texinfo` (chemins + couleurs) et `engine->map` et renseigne `engine->mapinfo.index_end_of_map`.
- En cas d'échec à n'importe quelle étape, la plupart des fonctions retournent `FAILURE` (ou `ERR`) et appellent `print_error_msg` pour fournir le message avant que l'appelant nettoie.

---

## Ordre recommandé pour maîtriser/maintenir le parsing

1. Lire `load_cub_file` pour comprendre comment le fichier est chargé en mémoire.
2. Lire `get_file_data` et `parse_line_` (cœur du parser) — comprendre la logique d'analyse caractère par caractère.
3. Examiner `parse_direction_texture`, `extract_texture_path`, `parse_floor_ceiling_color` — la façon dont les tokens sont extraits.
4. Examiner `parse_map_layout` et ses helpers (`count_map_height`, `build_map_array`) pour comprendre comment la map devient un tableau rectangulaire.
5. Lire les validations (`validate_file`, `validate_textures_and_colors`, `validate_map*`) pour comprendre les vérifications de sécurité.
6. Vérifier l'initialisation (`init_engine`) et le cleanup (`free_engine`, `clean_exit`) pour s'assurer des invariants (pointeurs initialisés avant free).

---

## Pièges évités / difficultés rencontrées (et comment ils sont gérés)

1. Lecture du fichier : gérer correctement la mémoire (allocation du tableau de lignes). Solution : compter les lignes d'abord puis allouer.
2. Format des couleurs : espaces autour des nombres, validation stricte et trimming. Solution : `ft_strtrim`, `is_strict_digit_str`, contrôle du nombre de virgules.
3. Chemins textures : vérifier qu'il n'y a pas d'extra sur la ligne après le chemin, empêcher les doubles définitions.
4. Map non-rectangulaire et espaces internes : paddings et remplacement des espaces internes par des murs afin d'éviter des trous non-intentionnels.
5. Player placement : s'assurer d'une et une seule position. Placer le joueur au centre de la tuile et vérifier l'enclosure pour éviter des accès hors-borne.
6. Fuite mémoire en cas d'erreur en milieu de parsing : nombreuses fonctions libèrent leurs allocations temporaires (`free_2d_array`) et retournent des codes d'erreur.
7. Différences OS pour la gestion souris/MLX : wrappers `mlx_*_platform.c` (Linux vs macOS) évitent le mélange de calls spécifiques.

---

## Ce que j'ai appris / conseils pratiques

- Séparer la lecture brute (charger en mémoire) du parsing logique facilite le code (un flux d'étapes clair).
- Toujours valider les entrées (extens., format, existance fichier) avant d'utiliser les valeurs (ex : `mlx_xpm_file_to_image`).
- Pour les maps, préférer une représentation rectangulaire pour simplifier la logique (indexations & validations).
- Implémenter des helpers de debug (print) pour inspecter l'état après le parsing.
- Toujours initialiser les structures (init_*) et vérifier lors du cleanup pour éviter double-free ou frees invalides.

---

## Tests et vérifications à faire

- Tester avec fichiers `.cub` corrects et malformés :
  - textures manquantes, mauvaises extensions, chemins non existants
  - couleurs mal formatées (trop de virgules, lettre dans un composant)
  - map non fermée
  - player manquant ou multiple
  - contenu après la map
- Utiliser les fonctions de debug après `get_file_data` pour imprimer l'état et vérifier.

---

## Améliorations possibles (petites, sûres)

- Remplacer la lecture en deux passes (count + load) par une lecture dynamique (liste chainée) pour simplifier la logique si la taille est inconnue.
- Fournir des messages d'erreur plus précis (ligne/col où l'erreur de parsing est détectée) pour faciliter le debugging.
- Automatiser des tests unitaires (ex : plusieurs .cub de test et un runner) pour valider les cas limites.

---

## Conclusion — résumé simple et actionnable

Le parsing est organisé en trois grandes étapes : initialisation (mettre tout à NULL/0), lecture brute du fichier en mémoire (avec `load_cub_file`), puis parsing séquentiel ligne-par-ligne (`get_file_data`/`parse_line_`) qui remplit `texinfo` et `map` et se termine par une série de validations (`validate_*`). Le code est robuste : il vérifie les formats, libère correctement en cas d'erreur et initialise/clean proprement.

Si tu veux, je peux :
- Ajouter des commentaires inline supplémentaires dans les fonctions les plus critiques.
- Générer un diagramme d'appel ou une carte mentale du flux parsing.
- Ajouter des tests unitaires / jeux de données `.cub` pour valider automatiquement les cas d'erreur.


---

*Fichier généré automatiquement par l'analyse du dépôt — PARSING_NOTE.md*
