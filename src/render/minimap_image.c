/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:45:51 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 00:32:29 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap_border_into_frame(t_image *frame,
				t_minimap_ctx *minimap);

static void	fill_minimap_tile_into_frame(t_image *frame,
		t_minimap_ctx *minimap, int x_idx, int y_idx)
{
	int	px;
	int	py;
	int	i;
	int	color;

	px = minimap->draw_off_x + x_idx * minimap->tile_size;
	py = minimap->draw_off_y + y_idx * minimap->tile_size;
	if (minimap->map[y_idx][x_idx] == 'P')
		color = MINIMAP_COLOR_PLAYER;
	else if (minimap->map[y_idx][x_idx] == '1')
		color = MINIMAP_COLOR_WALL;
	else if (minimap->map[y_idx][x_idx] == '0')
		color = MINIMAP_COLOR_FLOOR;
	else
		color = MINIMAP_COLOR_SPACE;
	i = 0;
	while (i < minimap->tile_size * minimap->tile_size)
	{
		set_image_pixel(frame, color,
			px + (i % minimap->tile_size), py + (i / minimap->tile_size));
		i++;
	}
}

static void	render_minimap_row_into_frame(t_image *frame,
		t_minimap_ctx *minimap, int y)
{
	int	x;

	x = 0;
	while (x < minimap->size)
	{
		if (!minimap->map[y] || !minimap->map[y][x])
			break ;
		fill_minimap_tile_into_frame(frame, minimap, x, y);
		x++;
	}
}

static void	render_minimap_grid_into_frame(t_image *frame,
		t_minimap_ctx *minimap)
{
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		render_minimap_row_into_frame(frame, minimap, y);
		y++;
	}
	draw_minimap_border_into_frame(frame, minimap);
}

static void	draw_minimap_border_into_frame(t_image *frame,
		t_minimap_ctx *minimap)
{
	int	size;
	int	ry;
	int	rx;

	size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	ry = 0;
	while (ry < size)
	{
		rx = 0;
		while (rx < size)
		{
			if (rx < 5 || rx > size - 5 || ry < 5 || ry > size - 5)
				set_image_pixel(frame, MINIMAP_COLOR_SPACE,
					minimap->draw_off_x + rx, minimap->draw_off_y + ry);
			rx++;
		}
		ry++;
	}
}

/**
 * @brief Render the minimap into the provided frame image.
 *
 * @param engine Pointer to engine.
 * @param frame Target frame image where the minimap will be drawn.
 * @param minimap Minimapa context (map/grid already computed).
 */
void	render_minimap_image_into_frame(t_engine *engine, t_image *frame,
		t_minimap_ctx *minimap)
{
	int	off_x;
	int	off_y;

	off_x = engine->win_width - (MINIMAP_PIXEL_SIZE + (minimap->tile_size * 2));
	off_y = minimap->tile_size;
	minimap->draw_off_x = off_x;
	minimap->draw_off_y = off_y;
	render_minimap_grid_into_frame(frame, minimap);
}
