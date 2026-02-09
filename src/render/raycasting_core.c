/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:18:56 by mbah              #+#    #+#             */
/*   Updated: 2026/02/03 17:37:37 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize ray values for the current screen column.
 *
 * Computes ray direction, camera position, delta distances
 * and starting map cell.
 *
 * @param x Current screen column.
 * @param ray Pointer to raycast structure.
 * @param player Pointer to player data.
 */
static void	init_raycast_info(int x, t_raycast *ray, t_player *player)
{
	init_raycast(ray);
	ray->camera_x = 2.0 * x / (double)WIN_WIDTH - 1.0;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1.0 / ray->dir_x);
	ray->deltadist_y = fabs(1.0 / ray->dir_y);
}

/**
 * @brief Initialize DDA stepping direction and side distances.
 *
 * Determines ray step direction and initial distance to the
 * first grid boundary.
 *
 * @param ray Pointer to raycast structure.
 * @param player Pointer to player data.
 */
static void	init_dda_step(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x)
			* ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y)
			* ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->deltadist_y;
	}
}

/**
 * @brief Perform the DDA (Digital Differential Analyzer) 
 * algorithm to detect wall collision.
 *
 * Steps through the map grid until a wall is hit or
 * bounds are exceeded.
 *
 * @param engine Pointer to engine data.
 * @param ray Pointer to raycast structure.
 */
static void	execute_dda(t_engine *engine, t_raycast *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0.25
			|| ray->map_y < 0.25
			|| ray->map_x > engine->mapinfo.width - 1.25
			|| ray->map_y > engine->mapinfo.height - 0.25)
			break ;
		if (engine->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

/**
 * @brief Compute wall distance and vertical line projection.
 *
 * Calculates wall distance, line height, draw range
 * and texture coordinate.
 *
 * @param ray Pointer to raycast structure.
 * @param engine Pointer to engine data.
 * @param player Pointer to player data.
 */
static void	compute_wall_projection(t_raycast *ray,
									t_engine *engine,
									t_player *player)
{
	if (ray->side == 0)
		ray->wall_dist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->wall_dist = ray->sidedist_y - ray->deltadist_y;
	ray->line_height = (int)(engine->win_height / ray->wall_dist);
	ray->draw_start = engine->win_height / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = engine->win_height / 2 + ray->line_height / 2;
	if (ray->draw_end >= engine->win_height)
		ray->draw_end = engine->win_height - 1;
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = player->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
}

/**
 * @brief Perform raycasting for the entire screen.
 *
 * Casts one ray per screen column and updates texture rendering.
 *
 * @param player Pointer to player data.
 * @param engine Pointer to engine data.
 * @return SUCCESS on completion.
 */
int	perform_raycasting(t_player *player, t_engine *engine)
{
	t_raycast	ray;
	int			x;

	x = 0;
	ray = engine->ray;
	while (x < engine->win_width)
	{
		init_raycast_info(x, &ray, player);
		init_dda_step(&ray, player);
		execute_dda(engine, &ray);
		compute_wall_projection(&ray, engine, player);
		render_wall_texture_column(engine, &engine->texinfo, &ray, x);
		x++;
	}
	return (SUCCESS);
}
