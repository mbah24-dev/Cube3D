/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:18:05 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 17:02:20 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init_engine.c
 * @brief Initializes all components of the cub3D engine to default values.
 */

#include "cub3d.h"

/**
 * @brief Initialize the image structure to default values.
 *
 * Sets all fields of the t_image structure to NULL or zero.
 *
 * @param img Pointer to the image structure to initialize.
 */
void	init_image(t_image *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

/**
 * @brief Initialize the raycasting structure to default values.
 *
 * Sets all fields of the t_raycast structure to zero or default states.
 *
 * @param ray Pointer to the raycasting structure to initialize.
 */
void	init_raycast(t_raycast *ray)
{
	ray->camera_x = 0.0;
	ray->dir_x = 0.0;
	ray->dir_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0.0;
	ray->sidedist_y = 0.0;
	ray->deltadist_x = 0.0;
	ray->deltadist_y = 0.0;
	ray->wall_dist = 0.0;
	ray->wall_x = 0.0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

/**
 * @brief Initialize the map context structure to default values.
 *
 * Sets all fields of the t_map_context structure to zero or default states.
 *
 * @param map Pointer to the map context structure to initialize.
 */
static void	init_map_context(t_map_context *map)
{
	map->fd = -1;
	map->line_count = 0;
	map->path = NULL;
	map->file = NULL;
	map->height = 0;
	map->width = 0;
	map->index_end_of_map = 0;
}

/**
 * @brief Initialize the player structure to default values.
 *
 * Sets all fields of the t_player structure to zero or default states.
 *
 * @param player Pointer to the player structure to initialize.
 */
static void	init_player(t_player *player)
{
	player->dir = '\0';
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
}

/**
 * @brief Initialize the main engine structure to default values.
 *
 * Sets all fields of the t_engine structure to NULL, zero, or default states.
 *
 * @param engine Pointer to the main engine structure to initialize.
 */
void	init_engine(t_engine *engine)
{
	engine->mlx = NULL;
	engine->win = NULL;
	engine->win_width = WIN_WIDTH;
	engine->win_height = WIN_HEIGHT;
	engine->map = NULL;
	engine->texture_pixels = NULL;
	engine->textures = NULL;
	init_player(&engine->player);
	init_raycast(&engine->ray);
	init_texture_info(&engine->texinfo);
	init_map_context(&engine->mapinfo);
	init_image(&engine->minimap);
}
