/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:36:02 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 14:21:10 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_config.c
 * @brief Main configuration file parsing functions for the cub3D engine.
 *
 * This file contains the main logic to read the configuration file line by line,
 * extract texture paths, floor and ceiling colors, and map layout. It ensures
 * that the configuration is valid and properly stored in the engine's data
 * structures for later use in rendering and game logic.
 */

#include "cub3d.h"

/**
 * @brief Extracts a texture path from a configuration line.
 *
 * Skips leading whitespaces, copies the path, and ensures
 * there is no extra unexpected content after it.
 *
 * @param line Configuration line.
 * @param start Index where the path is expected.
 * @return Allocated path string or NULL on error.
 */
static char	*extract_texture_path(char *line, int start)
{
	int		end;
	int		i;
	char	*path;

	while (line[start] == ' ' || line[start] == '\t')
		start++;
	end = start;
	while (line[end] && line[end] != ' ' && line[end] != '\t')
		end++;
	path = malloc(sizeof(char) * (end - start + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (start < end && line[start] != '\n')
		path[i++] = line[start++];
	path[i] = '\0';
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	if (line[start] && line[start] != '\n')
	{
		free(path);
		return (NULL);
	}
	return (path);
}

/**
 * @brief Assigns directional texture paths.
 *
 * Handles NO, SO, WE, EA identifiers.
 *
 * @param tex Texture info structure.
 * @param line Configuration line.
 * @param index Index of the identifier.
 * @return SUCCESS or ERR.
 */
static int	parse_direction_texture(t_texture_info *tex,
					char *line, int index)
{
	if (!line[index + 2] || (line[index + 2] != ' '
			&& line[index + 2] != '\t'))
		return (ERR);
	if (line[index] == 'N' && line[index + 1] == 'O' && !tex->north)
		tex->north = extract_texture_path(line, index + 2);
	else if (line[index] == 'S' && line[index + 1] == 'O' && !tex->south)
		tex->south = extract_texture_path(line, index + 2);
	else if (line[index] == 'W' && line[index + 1] == 'E' && !tex->west)
		tex->west = extract_texture_path(line, index + 2);
	else if (line[index] == 'E' && line[index + 1] == 'A' && !tex->east)
		tex->east = extract_texture_path(line, index + 2);
	else
		return (ERR);
	return (SUCCESS);
}

/**
 * @brief Advances column index past whitespace characters.
 *
 * @param row Current line index.
 * @param col Current column index.
 * @param file File content.
 * @return New column index after skipping spaces, tabs, and newlines.
 */
static int	get_new_col_after_spaces(int row, int col, char **file)
{
	while (file[row][col] == ' ' || file[row][col] == '\t'
		|| file[row][col] == '\n')
		col++;
	return (col);
}

/**
 * @brief Skips whitespaces and identifies configuration content.
 *
 * Determines whether the line contains textures, colors, or the map.
 *
 * @param data Main data structure.
 * @param file File content.
 * @param row Current line index.
 * @param col Current column index.
 * @return CONTINUE, BREAK, SUCCESS or FAILURE.
 */
static int	parse_line_(t_engine *data, char **file, int row, int col)
{
	col = get_new_col_after_spaces(row, col, file);
	if (ft_isalpha(file[row][col]) && !ft_isdigit(file[row][col]))
	{
		if (file[row][col + 1] && ft_isalpha(file[row][col + 1])
			&& !ft_isdigit(file[row][col + 1]))
		{
			if (parse_direction_texture(&data->texinfo,
					file[row], col) == ERR)
				return (print_error_msg(data->mapinfo.path,
						ERROR_TEX_INVALID, FAILURE));
			return (BREAK);
		}
		if (parse_floor_ceiling_color(data, &data->texinfo,
				file[row], col) == ERR)
			return (FAILURE);
		return (BREAK);
	}
	if (ft_isdigit(file[row][col]))
	{
		if (parse_map_layout(data, file, row) == FAILURE)
			return (print_error_msg(data->mapinfo.path,
					ERROR_INVALID_MAP, FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}

/**
 * @brief Parses the entire configuration file.
 *
 * Reads textures, colors, and map data in order.
 *
 * @param data Main data structure.
 * @param file File content.
 * @return SUCCESS or FAILURE.
 */
int	get_file_data(t_engine *data, char **file)
{
	int	row;
	int	col;
	int	ret;

	row = 0;
	while (file[row])
	{
		col = 0;
		while (file[row][col])
		{
			ret = parse_line_(data, file, row, col);
			if (ret == BREAK)
				break ;
			if (ret == FAILURE)
				return (FAILURE);
			if (ret == SUCCESS)
				return (SUCCESS);
			col++;
		}
		row++;
	}
	return (SUCCESS);
}
