/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:57:03 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 16:40:35 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include "libft.h"
# include "types.h"

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>

/* ************************************************************************** */
/*                       OPERATING SYSTEM DETECTION                           */
/* ************************************************************************** */

# ifdef __APPLE__

#  include "mlx.h"
#  include <ApplicationServices/ApplicationServices.h>

#  define KEY_ESC    53
#  define KEY_W      13
#  define KEY_A      0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_LEFT   123
#  define KEY_RIGHT  124

#  define MASK_KEY_PRESS        0
#  define MASK_KEY_RELEASE      0
#  define MASK_BUTTON_PRESS     0
#  define MASK_BUTTON_RELEASE   0
#  define MASK_POINTER_MOTION   0
#  define MASK_STRUCTURE_NOTIFY 0

# elif __linux__

#  include "mlx.h"
#  include <X11/keysym.h>
#  include <X11/X.h>

#  define KEY_ESC    65307
#  define KEY_W      119
#  define KEY_A      97
#  define KEY_S      115
#  define KEY_D      100
#  define KEY_LEFT   65361
#  define KEY_RIGHT  65363

#  define MASK_KEY_PRESS        0
#  define MASK_KEY_RELEASE      1
#  define MASK_BUTTON_PRESS     2
#  define MASK_BUTTON_RELEASE   3
#  define MASK_POINTER_MOTION   6
#  define MASK_STRUCTURE_NOTIFY 17

# else
#  error "Unsupported operating system"
# endif

/* ************************************************************************** */
/*                                   MACROS                                   */
/* ************************************************************************** */

# define WIN_WIDTH 1140
# define WIN_HEIGHT 780
# define TEX_SIZE 64

# ifndef DEBUG_MESSAGE
#  define DEBUG_MESSAGE 0
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# ifndef OS_MACOS
#  define OS_MACOS 0
# endif

# ifndef MMAP_DEBUG_MESSAGE
#  define MMAP_DEBUG_MESSAGE 0
# endif

/**
 * @def O_DIRECTORY
 * @brief Flag used with open() to ensure the given path refers to a directory.
 *
 * This flag forces the open() system call to succeed only if the provided
 * path is a directory. If the path refers to a regular file or does not
 * exist, open() will fail.
 *
 * Some systems or environments may not define O_DIRECTORY in <fcntl.h>.
 * This conditional definition ensures portability across different
 * Unix-based operating systems.
 *
 * The value 00200000 corresponds to the official Unix/Linux definition
 * of the O_DIRECTORY flag.
*/
# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.0125
# define ROTSPEED 0.015

/**
 * @def DIST_EDGE_MOUSE_WRAP
 * @brief Threshold distance (in pixels) from the window edges 
 * used to wrap the mouse cursor.
 *
 * This value defines how close the mouse cursor can get to the window borders
 * before it is automatically repositioned (wrapped). This technique is commonly
 * used in first-person applications to allow continuous camera rotation when
 * controlling the view with the mouse.
 *
 * When the cursor position is within DIST_EDGE_MOUSE_WRAP pixels from any
 * window edge, the cursor can be moved back to a safe position (usually the
 * center of the window) to maintain smooth and uninterrupted mouse input.
 *
 * This behavior is typically used in optional or bonus features and does not
 * affect the mandatory keyboard-based controls.
*/
# define DIST_EDGE_MOUSE_WRAP 20

/* ************************************************************************** */
/*                              MINIMAP MACROS                                */
/* ************************************************************************** */

# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_COLOR_PLAYER 0x00FF00
# define MINIMAP_COLOR_WALL 0x808080
# define MINIMAP_COLOR_FLOOR 0xE6E6E6
# define MINIMAP_COLOR_SPACE 0x404040

/* ************************************************************************** */
/*                              ERROR MESSAGES                                */
/* ************************************************************************** */

# define ERROR_USAGE \
"Utilisation : ./cub3D <chemin/vers/map.cub>"

# define ERROR_FILE_NOT_CUB \
"Le fichier fourni n'a pas l'extension .cub"

# define ERROR_FILE_NOT_XPM \
"Le fichier fourni n'a pas l'extension .xpm"

# define ERROR_FILE_IS_DIR \
"Le chemin fourni correspond à un dossier"

# define ERROR_FLOOR_CEILING \
"Couleurs du sol et/ou du plafond invalides"

# define ERROR_COLOR_FLOOR \
"Couleur du sol invalide"

# define ERROR_COLOR_CEILING \
"Couleur du plafond invalide"

# define ERROR_INVALID_MAP \
"Description de la carte incorrecte ou incomplète"

# define ERROR_INV_LETTER \
"Caractère invalide détecté dans la carte"

# define ERROR_NUM_PLAYER \
"La carte contient plus d'une position de joueur"

# define ERROR_TEX_RGB_VAL \
"Valeur RGB invalide (doit être comprise entre 0 et 255)"

# define ERROR_TEX_MISSING \
"Texture(s) manquante(s)"

# define ERROR_TEX_INVALID \
"Texture(s) invalide(s)"

# define ERROR_COLOR_MISSING \
"Couleur(s) manquante(s)"

# define ERROR_MAP_MISSING \
"Carte manquante dans le fichier"

# define ERROR_MAP_TOO_SMALL \
"La carte doit contenir au minimum 3 lignes"

# define ERROR_MAP_NO_WALLS \
"La carte n'est pas entièrement entourée de murs"

# define ERROR_MAP_LAST \
"La carte doit être le dernier élément du fichier"

# define ERROR_PLAYER_POS \
"Position du joueur invalide"

# define ERROR_PLAYER_DIR \
"Aucune position de joueur trouvée (N, S, E ou W attendue)"

# define ERROR_MALLOC \
"Échec de l'allocation mémoire"

# define ERROR_MLX_START \
"Impossible d'initialiser la MiniLibX"

# define ERROR_MLX_WIN \
"Impossible de créer la fenêtre graphique"

# define ERROR_MLX_IMG \
"Impossible de créer l'image graphique"

/* ************************************************************************** */
/*                                      FUNCTIONS                             */
/* ************************************************************************** */

/* ************************************************************************** */
/*                            VALIDATE_FILE FUNCTIONS                         */
/* ************************************************************************** */

int		validate_file(bool cub, char *path);

/* ************************************************************************** */
/*                              CLEANUP FUNCTIONS                             */
/* ************************************************************************** */

int		free_engine(t_engine *engine);
void	free_2d_array(void **array);

/* ************************************************************************** */
/*                              ERROR_HANDLING FUNCTIONS                      */
/* ************************************************************************** */

int		print_error_msg(char *detail, char *message, int code);
int		print_error_msg_int(int detail, char *message, int code);

/* ************************************************************************** */
/*                              EXIT_PROG FUNCTIONS                           */
/* ************************************************************************** */

void	clean_exit(t_engine *engine, int code);
int		quit_cub3d(t_engine *engine);

/* ************************************************************************** */
/*                              INIT_ENGINE FUNCTIONS                         */
/* ************************************************************************** */

void	init_engine(t_engine *engine);
void	init_raycast(t_raycast *ray);
void	init_image(t_image *img);

/* ************************************************************************** */
/*                              INIT_MLX FUNCTIONS                         */
/* ************************************************************************** */

void	init_image_mlx(t_engine *engine, t_image *image,
			int width, int height);
void	init_texture_image(t_engine *engine, t_image *image, char *path);
void	init_mlx(t_engine *engine);

/* ************************************************************************** */
/*                              INIT_TEXTURES FUNCTIONS                       */
/* ************************************************************************** */

void	init_texture_info(t_texture_info *texinfo);
void	init_textures(t_engine *engine);

/* ************************************************************************** */
/*                              INIT_DIRECTION FUNCTIONS                      */
/* ************************************************************************** */

void	init_player_direction_vectors(t_engine *engine);

/* ************************************************************************** */
/*                              MOVEMENT_COLLISION FUNCTIONS                  */
/* ************************************************************************** */

int		apply_player_movement(t_engine *engine, double new_x, double new_y);

/* ************************************************************************** */
/*                              ROTATION FUNCTIONS                            */
/* ************************************************************************** */

int		handle_player_rotation(t_engine *engine, double direction);

/* ************************************************************************** */
/*                              PLAYER_MOVEMENT FUNCTIONS                     */
/* ************************************************************************** */

int		update_player_movement(t_engine *engine);

/* ************************************************************************** */
/*                              INPUT_HANDLER FUNCTIONS                       */
/* ************************************************************************** */

void	register_input_hooks(t_engine *engine);

/* ************************************************************************** */
/*                              MAP_WALLS_VALIDATOR FUNCTIONS                 */
/* ************************************************************************** */

int		validate_map_walls(t_map_context *mapinfo, char **map);

/* ************************************************************************** */
/*                              MAP_UTILS FUNCTIONS                           */
/* ************************************************************************** */

int		is_blank(char c);
size_t	get_max_map_line_length(t_map_context *mapinfo, int start);

/* ************************************************************************** */
/*                              MAP_VALIDATION FUNCTIONS                      */
/* ************************************************************************** */

int		validate_map(t_engine *engine, char **map);

/* ************************************************************************** */
/*                              PARSE_COLOR FUNCTIONS                         */
/* ************************************************************************** */

int		parse_floor_ceiling_color(t_engine *data,
			t_texture_info *textures, char *line, int index);

/* ************************************************************************** */
/*                              VALIDATE_TEXTURES FUNCTIONS                   */
/* ************************************************************************** */

int		validate_textures_and_colors(t_engine *engine,
			t_texture_info *textures);

/* ************************************************************************** */
/*                              MAP_WALLS_VALIDATOR FUNCTIONS                 */
/* ************************************************************************** */

int		validate_map_walls(t_map_context *mapinfo, char **map);

/* ************************************************************************** */
/*                              PARSE_MAP_LAYOUT FUNCTIONS                    */
/* ************************************************************************** */

int		parse_map_layout(t_engine *data, char **file, int start);

#endif