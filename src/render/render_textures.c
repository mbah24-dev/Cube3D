/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:49:32 by mbah              #+#    #+#             */
/*   Updated: 2026/02/03 17:13:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Allocate and initialize the texture pixel buffer.
 *
 * This buffer stores the final rendered pixels column by column
 * before being displayed on screen.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_texture_pixel_buffer(t_engine *engine)
{
	int	i;

	if (engine->texture_pixels)
		free_2d_array((void **)engine->texture_pixels);
	engine->texture_pixels = ft_calloc(engine->win_height + 1,
			sizeof * engine->texture_pixels);
	if (!engine->texture_pixels)
		clean_exit(engine, print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	i = 0;
	while (i < engine->win_height)
	{
		engine->texture_pixels[i] = ft_calloc(engine->win_width + 1,
				sizeof * engine->texture_pixels);
		if (!engine->texture_pixels[i])
			clean_exit(engine, print_error_msg(NULL, ERROR_MALLOC, FAILURE));
		i++;
	}
}

/**
 * @brief Determine which wall texture should be used for the ray hit.
 *
 * The texture depends on:
 * - the side hit by the ray (X (0) or Y (1))
 * - the ray direction
 *
 * @param engine Pointer to the engine.
 * @param ray Pointer to the current raycast data.
 */
static void	select_wall_texture(t_engine *engine, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			engine->texinfo.index = WEST;
		else
			engine->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			engine->texinfo.index = SOUTH;
		else
			engine->texinfo.index = NORTH;
	}
}

/**
 * @brief Fill the texture pixel buffer for a single screen column.
 *
 * Computes the correct texture X/Y coordinates and maps the wall texture
 * vertically onto the screen column.
 *
 * @param engine Pointer to the engine.
 * @param tex Pointer to the texture info structure.
 * @param ray Pointer to the raycast result.
 * @param screen_x X coordinate of the screen column.
 */
void	render_wall_texture_column(t_engine *engine,
			t_texture_info *tex, t_raycast *ray, int screen_x)
{
	int	y;
	int	color;

	select_wall_texture(engine, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - engine->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = engine->textures[tex->index]
		[tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			engine->texture_pixels[y][screen_x] = color;
		y++;
	}
}
