/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 00:40:32 by mbah              #+#    #+#             */
/*   Updated: 2026/02/10 16:14:14 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Compute the starting offset of the minimap around the player.
 *
 * Ensures the minimap stays within map boundaries while keeping
 * the player centered when possible.
 *
 * @param minimap Pointer to minimap configuration.
 * @param map_size Total width or height of the map.
 * @param player_pos Player position on the given axis.
 * @return Offset index for the minimap.
 */
static int	compute_minimap_offset(t_minimap_ctx *minimap,
									int map_size,
									int player_pos)
{
	if (player_pos > minimap->view_dist
		&& map_size - player_pos > minimap->view_dist + 1)
		return (player_pos - minimap->view_dist);
	if (player_pos > minimap->view_dist
		&& map_size - player_pos <= minimap->view_dist + 1)
		return (map_size - minimap->size);
	return (0);
}

/**
 * @brief Check if a coordinate is inside map bounds.
 *
 * @param coord Coordinate to check.
 * @param size Map dimension.
 * @return true if valid, false otherwise.
 */
static bool	is_inside_map_bounds(int coord, int size)
{
	return (coord < size);
}

/**
 * @brief Build a single row of the minimap.
 *
 * Creates a string representing walls, floor, player or empty space.
 *
 * @param engine Pointer to global data.
 * @param minimap Pointer to minimap configuration.
 * @param y Row index inside minimap.
 * @return Newly allocated minimap row or NULL on failure.
 */
static char	*build_minimap_row(t_engine *data, t_minimap_ctx *minimap, int y)
{
	char	*row;
	int		x;

	row = ft_calloc(minimap->size + 1, sizeof(char));
	if (!row)
		return (NULL);
	x = -1;
	while (++x < minimap->size && x < data->mapinfo.width)
	{
		if (!is_inside_map_bounds(y + minimap->offset_y,
				data->mapinfo.height)
			|| !is_inside_map_bounds(x + minimap->offset_x,
				data->mapinfo.width))
			row[x] = '\0';
		else if ((int)data->player.pos_x == x + minimap->offset_x
			&& (int)data->player.pos_y == y + minimap->offset_y)
			row[x] = 'P';
		else if (data->map[y + minimap->offset_y][x + minimap->offset_x] == '1')
			row[x] = '1';
		else if (data->map[y + minimap->offset_y][x + minimap->offset_x] == '0')
			row[x] = '0';
		else
			row[x] = '\0';
	}
	return (row);
}

/**
 * @brief Generate the minimap grid around the player.
 *
 * @param engine Pointer to global data.
 * @param minimap Pointer to minimap configuration.
 * @return Allocated minimap grid or NULL on failure.
 */
static char	**build_minimap_grid(t_engine *engine, t_minimap_ctx *minimap)
{
	char	**grid;
	int		y;

	grid = ft_calloc(minimap->size + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	y = 0;
	while (y < minimap->size && y < engine->mapinfo.height)
	{
		grid[y] = build_minimap_row(engine, minimap, y);
		if (!grid[y])
		{
			free_2d_array((void **)grid);
			return (NULL);
		}
		y++;
	}
	return (grid);
}

/**
 * @brief Render the minimap overlay.
 *
 * Builds the minimap data, renders it, then frees allocated memory.
 *
 * @param data Pointer to global data.
 */
void	render_minimap_overlay(t_engine *engine)
{
	t_minimap_ctx	minimap;

	minimap.map = NULL;
	minimap.img = &engine->minimap;
	minimap.view_dist = MINIMAP_VIEW_DIST;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MINIMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	minimap.offset_x = compute_minimap_offset(&minimap,
			engine->mapinfo.width, (int)engine->player.pos_x);
	minimap.offset_y = compute_minimap_offset(&minimap,
			engine->mapinfo.height, (int)engine->player.pos_y);
	minimap.map = build_minimap_grid(engine, &minimap);
	if (!minimap.map)
	{
		print_error_msg(NULL, ERROR_MALLOC, 0);
		return ;
	}
	render_minimap_image(engine, &minimap);
	free_2d_array((void **)minimap.map);
}
