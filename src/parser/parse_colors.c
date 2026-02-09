/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 00:35:55 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 14:17:49 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks whether a string contains no digit characters.
 *
 * @param str The string to check.
 * @return true if no digit is found, false otherwise.
 */
static bool	contains_no_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
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
static int	*parse_rgb_values(char **rgb_parts, int *rgb)
{
	int	i;

	i = 0;
	while (rgb_parts[i])
	{
		rgb[i] = ft_atoi(rgb_parts[i]);
		if (rgb[i] < 0 || contains_no_digit(rgb_parts[i]))
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
