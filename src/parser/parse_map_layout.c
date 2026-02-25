/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:21 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 17:36:16 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_map_layout.c
 * @brief Functions to parse and build the map layout 
 * from the configuration file.
 *
 * This file contains functions to extract the map layout 
 * from the .cub file content,
 * determine its dimensions, allocate memory for the map array, and fill it with
 * the appropriate characters. It also includes logic to replace inner whitespace
 * with walls to ensure a valid map structure.
 */

#include "cub3d.h"

/**
 * @brief Counts the number of valid map lines starting at a given index.
 *
 * A valid map line must start with a wall character ('1'),
 * ignoring leading whitespace.
 *
 * @param data Pointer to the engine context.
 * @param file Full file content split into lines.
 * @param start Index where the map starts.
 * @return Number of map lines detected.
 */
static int	count_map_height(t_engine *data, char **file, int start)
{
	int	index;
	int	j;

	index = start;
	while (file[index])
	{
		j = 0;
		while (file[index][j] == ' ' || file[index][j] == '\t'
			|| file[index][j] == '\r' || file[index][j] == '\v'
			|| file[index][j] == '\f')
			j++;
		if (file[index][j] != '1')
			break ;
		index++;
	}
	data->mapinfo.index_end_of_map = index;
	return (index - start);
}

/**
 * @brief Allocates and fills the map array from the file content.
 *
 * Each map line is padded to the maximum map width.
 *
 * @param mapinfo Pointer to the map context.
 * @param map Destination map array.
 * @param start Index of the first map line.
 * @return SUCCESS on success, FAILURE on error.
 */
static int	build_map_array(t_map_context *mapinfo, char **map, int start)
{
	int	i;
	int	j;

	mapinfo->width = get_max_map_line_length(mapinfo, start);
	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map[i])
			return (print_error_msg(NULL, ERROR_MALLOC, FAILURE));
		while (mapinfo->file[start][j]
			&& mapinfo->file[start][j] != '\n')
		{
			map[i][j] = mapinfo->file[start][j];
			j++;
		}
		while (j < mapinfo->width)
			map[i][j++] = '\0';
		map[i][j] = '\0';
		i++;
		start++;
	}
	map[i] = NULL;
	return (SUCCESS);
}

/**
 * @brief Extracts map dimensions and allocates the map array.
 *
 * @param data Pointer to the engine context.
 * @param file Full file content.
 * @param start Index where the map starts.
 * @return SUCCESS on success, FAILURE on error.
 */
static int	extract_map_data(t_engine *data, char **file, int start)
{
	data->mapinfo.height = count_map_height(data, file, start);
	data->map = malloc(sizeof(char *) * (data->mapinfo.height + 1));
	if (!data->map)
		return (print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	if (build_map_array(&data->mapinfo, data->map, start) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Replaces inner whitespace characters with walls.
 *
 * This ensures that spaces inside the map are treated as solid walls,
 * preventing invalid map openings.
 *
 * @param data Pointer to the engine context.
 */
static void	replace_inner_spaces_with_walls(t_engine *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
			|| data->map[i][j] == '\r'
			|| data->map[i][j] == '\v'
			|| data->map[i][j] == '\f')
			j++;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == ' '
				&& j != (int)ft_strlen(data->map[i]) - 1)
				data->map[i][j] = '1';
		}
		i++;
	}
}

/**
 * @brief Parses and builds the playable map layout.
 *
 * @param data Pointer to the engine context.
 * @param file Full file content.
 * @param start Index where the map starts.
 * @return SUCCESS on success, FAILURE on error.
 */
int	parse_map_layout(t_engine *data, char **file, int start)
{
	if (extract_map_data(data, file, start) == FAILURE)
		return (FAILURE);
	replace_inner_spaces_with_walls(data);
	return (SUCCESS);
}
