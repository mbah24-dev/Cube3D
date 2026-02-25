/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:35:55 by mbah              #+#    #+#             */
/*   Updated: 2026/02/10 17:08:56 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_colors.c
 * @brief Functions to parse floor and ceiling 
 * color definitions from the map file.
 *
 * This file contains functions to extract RGB color 
 * values for the floor and ceiling
 * from the map file, validate their format, 
 * and store them in the engine's texture
 * information structure.
 */

#include "cub3d.h"

/**
 * @brief Checks whether a string is composed only of digits.
 *
 * @param str The string to check.
 * @return true if all characters are digits, false otherwise.
 */
static bool	is_strict_digit_str(char *str)
{
	int	i;

	if (!str || !str[0])
		return (false);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Converts a split RGB string array into an integer RGB array.
 *
 * This function parses each RGB component, checks validity,
 * and fills the provided integer array.
 *
 * @param rgb_parts Array of strings containing RGB components.
 * @param rgb Destination integer array.
 * @return The filled RGB array on success, NULL on failure.
 */
static int	parse_rgb_value(char *part, int *out)
{
	char	*trimmed;

	trimmed = ft_strtrim(part, " \t\r\n\v\f");
	if (!trimmed)
		return (0);
	if (!is_strict_digit_str(trimmed))
	{
		free(trimmed);
		return (0);
	}
	*out = ft_atoi(trimmed);
	free(trimmed);
	if (*out < 0)
		return (0);
	return (1);
}

/**
 * @brief Parses RGB components from a split 
 * string array and fills the RGB array.
 * @return The filled RGB array on success, NULL on failure.
 */
static int	*parse_rgb_values(char **rgb_parts, int *rgb)
{
	int	i;

	i = 0;
	while (rgb_parts[i])
	{
		if (!parse_rgb_value(rgb_parts[i], &rgb[i]))
		{
			free_2d_array((void **)rgb_parts);
			free(rgb);
			return (NULL);
		}
		i++;
	}
	free_2d_array((void **)rgb_parts);
	return (rgb);
}

/**
 * @brief Extracts RGB values from a floor or ceiling definition line.
 *
 * The expected format is: "R,G,B".
 *
 * @param line The string containing RGB values.
 * @return An allocated RGB array on success, NULL on failure.
 */
static int	*extract_rgb_from_line(char *line)
{
	char	**rgb_parts;
	int		*rgb;
	int		count;

	if (!line_contains_exactly_two_commas(line))
		return (NULL);
	rgb_parts = ft_split(line, ',');
	count = 0;
	while (rgb_parts[count])
		count++;
	if (count != 3)
	{
		free_2d_array((void **)rgb_parts);
		return (NULL);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		print_error_msg(NULL, ERROR_MALLOC, FAILURE);
		free_2d_array((void **)rgb_parts);
		return (NULL);
	}
	return (parse_rgb_values(rgb_parts, rgb));
}

/**
 * @brief Parses and stores floor or ceiling color information.
 *
 * Handles 'F' (floor) and 'C' (ceiling) color definitions.
 *
 * @param data Pointer to the main engine structure.
 * @param textures Pointer to the texture information structure.
 * @param line Line currently being parsed.
 * @param index Index of the identifier character ('F' or 'C').
 *
 * @return SUCCESS on success, ERR on failure.
 */
int	parse_floor_ceiling_color(t_engine *data,
								t_texture_info *textures,
								char *line,
								int index)
{
	if (!line[index + 1] || (line[index + 1] != ' '
			&& line[index + 1] != '\t'))
		return (print_error_msg(data->mapinfo.path, ERROR_FLOOR_CEILING, ERR));
	if (!textures->ceiling && line[index] == 'C')
	{
		textures->ceiling = extract_rgb_from_line(&line[index + 1]);
		if (!textures->ceiling)
			return (print_error_msg(data->mapinfo.path,
					ERROR_COLOR_CEILING, ERR));
	}
	else if (!textures->floor && line[index] == 'F')
	{
		textures->floor = extract_rgb_from_line(&line[index + 1]);
		if (!textures->floor)
			return (print_error_msg(data->mapinfo.path,
					ERROR_COLOR_FLOOR, ERR));
	}
	else
		return (print_error_msg(data->mapinfo.path, ERROR_FLOOR_CEILING, ERR));
	return (SUCCESS);
}
