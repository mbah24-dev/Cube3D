/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 15:27:13 by mbah              #+#    #+#             */
/*   Updated: 2026/01/29 15:49:35 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file map_utils.c
 * @brief Utility functions for map parsing and validation in the cub3D engine.
 */

#include "cub3d.h"

/**
 * @brief Check whether a character is considered whitespace.
 *
 * This function tests if the given character belongs to the set of
 * whitespace characters allowed in map files:
 * space, tab, carriage return, newline, vertical tab, or form feed.
 *
 * @param c Character to test.
 * @return SUCCESS if the character is a whitespace, FAILURE otherwise.
 */
int	is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Find the maximum line length in a map file starting from an index.
 *
 * This function iterates through the map file lines starting at index `start`
 * and returns the length of the longest line encountered.
 *
 * It is typically used to determine the effective width of the map and
 * to help normalize map rows during parsing.
 *
 * @param mapinfo Pointer to the map context structure.
 * @param start Index of the first line to consider.
 * @return Length of the longest line.
 */
size_t	get_max_map_line_length(t_map_context *mapinfo, int start)
{
	size_t	max_length;

	max_length = ft_strlen(mapinfo->file[start]);
	while (mapinfo->file[start])
	{
		if (max_length < ft_strlen(mapinfo->file[start]))
			max_length = ft_strlen(mapinfo->file[start]);
		start++;
	}
	return (max_length);
}

/**
 * @brief Check if a line contains exactly two commas.
 *
 * This function counts the number of comma characters in the given line
 * and returns true if there are exactly two, which is expected for RGB
 * color definitions in the map file.
 *
 * @param line The string to check.
 * @return 1 if the line contains exactly two commas, 0 otherwise.
 */
int	line_contains_exactly_two_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}
