/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:51:18 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 02:24:51 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_file.c
 * @brief Functions to validate input files 
 * (.cub and .xpm) for cub3D.
*/
#include "cub3d.h"

/**
 * @brief Checks if the given path corresponds to a directory.
 *
 * @param path The file path to check.
 * @return true if path is a directory, false otherwise.
*/
static bool	is_directory(char *path)
{
	int		fd;
	bool	ret_value;

	ret_value = false;
	fd = open(path, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		ret_value = true;
	}
	return (ret_value);
}

/**
 * @brief Checks if the given filename has a ".cub" extension.
 *
 * @param filename The name of the file.
 * @return true if filename ends with ".cub", false otherwise.
*/
static bool	has_cub_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || filename[len - 4] != '.' || filename[len - 3] != 'c'
		|| filename[len - 2] != 'u' || filename[len - 1] != 'b')
		return (false);
	return (true);
}

/**
 * @brief Checks if the given filename has a ".xpm" extension.
 *
 * @param filename The name of the file.
 * @return true if filename ends with ".xpm", false otherwise.
*/
static bool	has_xpm_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || filename[len - 4] != '.' || filename[len - 3] != 'x'
		|| filename[len - 2] != 'p' || filename[len - 1] != 'm')
		return (false);
	return (true);
}

/**
 * @brief Validates a file by checking its existence, type, and extension.
 *
 * This function verifies:
 * 1. The file exists and is not a directory.
 * 2. The file can be opened for reading.
 * 3. The file has the correct extension 
 * (".cub" if cub is true, ".xpm" if false).
 *
 * @param path Path to the file to validate.
 * @param cub Boolean indicating whether the file should be 
 * a .cub file (true) or a .xpm file (false).
 * @return SUCCESS if the file is valid, FAILURE otherwise
 * (prints an error message).
*/
int	validate_file(bool cub, char *path)
{
	int	fd;

	if (is_directory(path))
		return (print_error_msg(path, ERROR_FILE_IS_DIR, FAILURE));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error_msg(path, strerror(errno), FAILURE));
	close(fd);
	if (cub && !has_cub_extension(path))
		return (print_error_msg(path, ERROR_FILE_NOT_CUB, FAILURE));
	if (!cub && !has_xpm_extension(path))
		return (print_error_msg(path, ERROR_FILE_NOT_XPM, FAILURE));
	return (SUCCESS);
}
