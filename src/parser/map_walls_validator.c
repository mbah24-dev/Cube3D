/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_validator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:36:50 by mbah              #+#    #+#             */
/*   Updated: 2026/01/29 15:49:40 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_walls_validator.c
 * @brief Functions to validate that the map is properly enclosed by walls.
 *
 * This file contains functions to check that the map is fully surrounded
 * by '1' characters, ensuring that the player cannot exit the map boundaries.
 */

#include "cub3d.h"

/**
 * @brief Check that a full map line is composed only of walls.
 *
 * This function skips leading whitespace characters, then verifies that
 * all remaining characters in the line are wall tiles ('1').
 *
 * It is used to validate the top and bottom borders of the map.
 *
 * @param map Array of map lines.
 * @param row Index of the line to check.
 * @param col Starting column index (usually 0).
 * @return SUCCESS if the line is valid, FAILURE otherwise.
 */
static int	is_wall_only_line(char **map, int row, int col)
{
	if (!map || !map[row] || !map[row][col])
		return (FAILURE);
	while (map[row][col] == ' ' || map[row][col] == '\t'
		|| map[row][col] == '\r' || map[row][col] == '\v'
		|| map[row][col] == '\f')
		col++;
	while (map[row][col])
	{
		if (map[row][col] != '1')
			return (FAILURE);
		col++;
	}
	return (SUCCESS);
}

/**
 * @brief Validate that the map is fully surrounded by walls.
 *
 * This function checks:
 * - The top line of the map contains only wall tiles
 * - The bottom line of the map contains only wall tiles
 * - Each middle line starts and ends with a wall tile
 *
 * This ensures the player can never exit the map boundaries.
 *
 * @param mapinfo Pointer to the map context structure.
 * @param map Array of map lines.
 * @return SUCCESS if the map is properly enclosed, FAILURE otherwise.
 */
int	validate_map_walls(t_map_context *mapinfo, char **map)
{
	int	row;
	int	last_col;

	if (is_wall_only_line(map, 0, 0) == FAILURE)
		return (FAILURE);
	row = 1;
	while (row < (mapinfo->height - 1))
	{
		last_col = ft_strlen(map[row]) - 1;
		if (map[row][last_col] != '1')
			return (FAILURE);
		row++;
	}
	if (is_wall_only_line(map, row, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
