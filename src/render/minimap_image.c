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

/**
 * @brief Fill a minimap tile with a single color.
 *
 * Draws a square tile of size tile_size x tile_size
 * at the given pixel coordinates.
 *
 * @param minimap Pointer to the minimap structure.
 * @param px X pixel position.
 * @param py Y pixel position.
 * @param color Tile color.
 */
static void	fill_minimap_tile(t_minimap_ctx *minimap, int px, int py, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			set_image_pixel(minimap->img, color, px + j, py + i);
			j++;
		}
		i++;
	}
}

/**
 * @brief Render a single minimap tile based on map content.
 *
 * @param minimap Pointer to the minimap structure.
 * @param x Tile X index.
 * @param y Tile Y index.
 */
static void	render_minimap_tile(t_minimap_ctx *minimap, int x, int y)
{
	int	px;
	int	py;

	px = x * minimap->tile_size;
	py = y * minimap->tile_size;
	if (minimap->map[y][x] == 'P')
		fill_minimap_tile(minimap, px, py, MINIMAP_COLOR_PLAYER);
	else if (minimap->map[y][x] == '1')
		fill_minimap_tile(minimap, px, py, MINIMAP_COLOR_WALL);
	else if (minimap->map[y][x] == '0')
		fill_minimap_tile(minimap, px, py, MINIMAP_COLOR_FLOOR);
	else if (minimap->map[y][x] == ' ')
		fill_minimap_tile(minimap, px, py, MINIMAP_COLOR_SPACE);
}

/**
 * @brief Draw the minimap border.
 *
 * @param minimap Pointer to the minimap structure.
 * @param color Border color.
 */
static void	draw_minimap_border(t_minimap_ctx *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_image_pixel(minimap->img, color, x, y);
			x++;
		}
		y++;
	}
}

/**
 * @brief Render the entire minimap grid.
 *
 * @param minimap Pointer to the minimap structure.
 */
static void	render_minimap_grid(t_minimap_ctx *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y] || !minimap->map[y][x])
				break ;
			render_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	draw_minimap_border(minimap, MINIMAP_COLOR_SPACE);
}

/**
 * @brief Render and display the minimap image.
 *
 * Creates the minimap image, renders its content,
 * displays it on screen, and destroys the image.
 *
 * @param data Pointer to the main data structure.
 * @param minimap Pointer to the minimap structure.
 */
void	render_minimap_image(t_engine *engine, t_minimap_ctx *minimap)
{
	int	img_size;

	img_size = MINIMAP_PIXEL_SIZE + minimap->tile_size;
	init_image_mlx(engine, &engine->minimap, img_size, img_size);
	render_minimap_grid(minimap);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->minimap.img,
		engine->win_width - (MINIMAP_PIXEL_SIZE + (minimap->tile_size * 2)),
		minimap->tile_size);
	mlx_destroy_image(engine->mlx, engine->minimap.img);
}
