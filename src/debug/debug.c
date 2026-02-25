/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:54:36 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 14:27:31 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file debug.c
 * @brief Debugging functions to print engine state and map information.
 */

#include "cub3d.h"

void	debug_print_char_tab(char **tab)
{
	int	i;

	printf("\n");
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

void	debug_display_minimap(t_minimap_ctx *minimap)
{
	printf("\n---- MINIMAP\n");
	printf("Minimap view distance: %d\n", minimap->view_dist);
	printf("Minimap size: %d * %d\n", minimap->size, minimap->size);
	debug_print_char_tab(minimap->map);
}

void	debug_display_mapinfo(t_engine *engine)
{
	printf("\n---- MAP\n");
	printf("Map height: %d\n", engine->mapinfo.height);
	printf("Map width: %d\n", engine->mapinfo.width);
	debug_print_char_tab(engine->map);
	printf("\n---- TEXTURES & COLORS\n");
	printf("Color ceiling: #%lx\n", engine->texinfo.hex_ceiling);
	printf("Color floor: #%lx\n", engine->texinfo.hex_floor);
	printf("Texture north: %s\n", engine->texinfo.north);
	printf("Texture south: %s\n", engine->texinfo.south);
	printf("Texture east: %s\n", engine->texinfo.east);
	printf("Texture west: %s\n", engine->texinfo.west);
}

void	debug_display_player(t_engine *engine)
{
	printf("\n---- PLAYER\n");
	printf("Player pos: ");
	printf("x = %f, y = %f\n", engine->player.pos_x, engine->player.pos_y);
	printf("Player direction: %c ", engine->player.dir);
	printf("(x = %f, y = %f)\n", engine->player.dir_x, engine->player.dir_y);
	printf("----------------- SYSTEM INFO -------------- \n");
	if (OS_MACOS == 1)
		printf("Vous etes sur MacOS\n");
	else
		printf("Vous n'etes pas sur MacOS\n");
}

void	debug_display_engine(t_engine *engine)
{
	debug_display_mapinfo(engine);
	debug_display_player(engine);
	printf("\n");
}
