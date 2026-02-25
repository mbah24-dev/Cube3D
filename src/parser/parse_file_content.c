/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:59:36 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 17:36:08 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file parse_file_content.c
 * @brief Functions to read the .cub file content into memory.
 *
 * This file contains functions to count the number of lines in the .cub file,
 * allocate memory for storing the file content, and read each line into an
 * array of strings for later parsing of textures, colors, and map layout.
 */

#include "cub3d.h"

/**
 * @brief Counts the number of lines in a file.
 *
 * Opens the file at the given path and reads it line by line
 * using get_next_line.
 *
 * @param path Path to the file.
 * @return Number of lines found.
 */
static int	count_file_lines(char *path)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		print_error_msg(path, strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (count);
}

/**
 * @brief Allocates and copies one line into the file array.
 *
 * @param data Pointer to engine context.
 * @param line Source line read from file.
 * @param index Destination index in file array.
 * @return SUCCESS or FAILURE.
 */
static int	store_file_line(t_engine *data, char *line, int index)
{
	int	i;

	data->mapinfo.file[index]
		= ft_calloc(ft_strlen(line) + 1, sizeof(char));
	if (!data->mapinfo.file[index])
		return (print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	i = 0;
	while (line[i])
	{
		data->mapinfo.file[index][i] = line[i];
		i++;
	}
	data->mapinfo.file[index][i] = '\0';
	return (SUCCESS);
}

/**
 * @brief Reads all lines from the opened file descriptor.
 *
 * Stores each line into data->mapinfo.file.
 *
 * @param data Pointer to engine context.
 */
static void	load_file_lines(t_engine *data)
{
	char	*line;
	int		line_index;

	line_index = 0;
	line = get_next_line(data->mapinfo.fd);
	while (line)
	{
		if (store_file_line(data, line, line_index) == FAILURE)
		{
			free(line);
			free_2d_array((void **)data->mapinfo.file);
			return ;
		}
		free(line);
		line = get_next_line(data->mapinfo.fd);
		line_index++;
	}
	data->mapinfo.file[line_index] = NULL;
}

/**
 * @brief Loads the entire .cub file into memory.
 *
 * Allocates an array of strings containing each line of the file.
 *
 * @param path Path to the .cub file.
 * @param data Pointer to the engine context.
 */
void	load_cub_file(char *path, t_engine *data)
{
	data->mapinfo.line_count = count_file_lines(path);
	data->mapinfo.path = path;
	data->mapinfo.file = ft_calloc(data->mapinfo.line_count + 1,
			sizeof(char *));
	if (!data->mapinfo.file)
	{
		print_error_msg(NULL, ERROR_MALLOC, FAILURE);
		return ;
	}
	data->mapinfo.fd = open(path, O_RDONLY);
	if (data->mapinfo.fd < 0)
		print_error_msg(path, strerror(errno), FAILURE);
	else
	{
		load_file_lines(data);
		close(data->mapinfo.fd);
	}
}
