/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:49:24 by mbah              #+#    #+#             */
/*   Updated: 2026/01/29 16:31:50 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_validation.c
 * @brief Functions to validate the map structure and 
 * player position for the cub3D engine.
 */

#include "cub3d.h"

/**
 * @brief Validate map characters and player uniqueness.
 *
 * This function checks that the map contains only valid characters:
 *  - '1' (wall)
 *  - '0' (empty space)
 *  - 'N', 'S', 'E', 'W' (player start)
 *
 * It also ensures that exactly one player position is defined.
 *
 * @param engine Pointer to the main engine structure.
 * @param map 2D array representing the map.
 * @return SUCCESS if valid, FAILURE otherwise.
 */
static int	validate_map_elements(t_engine *engine, char **map)
{
	int	y;
	int	x;

	y = 0;
	engine->player.dir = '0';
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			while (is_blank(map[y][x]) == SUCCESS)
				x++;
			if (!ft_strchr("10NSEW", map[y][x]))
				return (print_error_msg(engine->mapinfo.path,
						ERROR_INV_LETTER, FAILURE));
			if (ft_strchr("NSEW", map[y][x]) && engine->player.dir != '0')
				return (print_error_msg(engine->mapinfo.path,
						ERROR_NUM_PLAYER, FAILURE));
			if (ft_strchr("NSEW", map[y][x]) && engine->player.dir == '0')
				engine->player.dir = map[y][x];
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

/**
 * @brief Check whether the player starting position is enclosed.
 *
 * Ensures the player is not adjacent to whitespace or outside the map,
 * preventing invalid positions that could cause raycasting errors.
 *
 * @param engine Pointer to the main engine structure.
 * @param map 2D array representing the map.
 * @return SUCCESS if valid, FAILURE otherwise.
 */
static int	validate_player_enclosure(t_engine *engine, char **map)
{
	int	y;
	int	x;

	y = (int)engine->player.pos_y;
	x = (int)engine->player.pos_x;
	if (ft_strlen(map[y - 1]) < (size_t)x
		|| ft_strlen(map[y + 1]) < (size_t)x
		|| is_blank(map[y - 1][x]) == SUCCESS
		|| is_blank(map[y + 1][x]) == SUCCESS
		|| is_blank(map[y][x - 1]) == SUCCESS
		|| is_blank(map[y][x + 1]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Locate and initialize the player starting position.
 *
 * Converts the player character ('N', 'S', 'E', 'W') into a numeric position
 * centered inside its tile and replaces the map cell with '0'.
 * @note y_x[0] = y coordinate, y_x[1] = x coordinate
 * @param engine Pointer to the main engine structure.
 * @param map 2D array representing the map.
 * @return SUCCESS if valid, FAILURE otherwise.
 */
static int	init_player_position(t_engine *engine, char **map)
{
	int	y_x[2];

	if (engine->player.dir == '0')
		return (print_error_msg(engine->mapinfo.path,
				ERROR_PLAYER_DIR, FAILURE));
	y_x[0] = 0;
	while (map[y_x[0]])
	{
		y_x[1] = 0;
		while (map[y_x[0]][y_x[1]])
		{
			if (ft_strchr("NSEW", map[y_x[0]][y_x[1]]))
			{
				engine->player.pos_x = (double)y_x[1] + 0.5;
				engine->player.pos_y = (double)y_x[0] + 0.5;
				map[y_x[0]][y_x[1]] = '0';
			}
			y_x[1]++;
		}
		y_x[0]++;
	}
	if (validate_player_enclosure(engine, map) == FAILURE)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_PLAYER_POS, FAILURE));
	return (SUCCESS);
}

/**
 * @brief Ensure the map is the last element in the file.
 *
 * Checks that no non-whitespace characters exist after the map block
 * in the configuration file.
 *
 * @param mapinfo Pointer to the map context.
 * @return SUCCESS if valid, FAILURE otherwise.
 */
static int	validate_map_is_last(t_map_context *mapinfo)
{
	int	i;
	int	j;

	i = mapinfo->index_end_of_map;
	while (mapinfo->file[i])
	{
		j = 0;
		while (mapinfo->file[i][j])
		{
			if (is_blank(mapinfo->file[i][j]) == FAILURE)
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Perform full map validation.
 *
 * This function validates:
 *  - Map existence
 *  - Wall enclosure
 *  - Minimum size
 *  - Valid characters
 *  - Player position
 *  - Map placement in file
 *
 * @param engine Pointer to the main engine structure.
 * @param map 2D array representing the map.
 * @return SUCCESS if the map is valid, FAILURE otherwise.
 */
int	validate_map(t_engine *engine, char **map)
{
	if (!engine->map)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_MAP_MISSING, FAILURE));
	if (validate_map_walls(&engine->mapinfo, map) == FAILURE)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_MAP_NO_WALLS, FAILURE));
	if (engine->mapinfo.height < 3)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_MAP_TOO_SMALL, FAILURE));
	if (validate_map_elements(engine, map) == FAILURE)
		return (FAILURE);
	if (init_player_position(engine, map) == FAILURE)
		return (FAILURE);
	if (validate_map_is_last(&engine->mapinfo) == FAILURE)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_MAP_LAST, FAILURE));
	return (SUCCESS);
}
