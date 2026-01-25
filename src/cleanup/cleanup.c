/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:46:20 by mbah              #+#    #+#             */
/*   Updated: 2026/01/24 15:15:25 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file cleanup.c
 * @brief Functions to safely free memory allocated 
 * in the cub3D engine.
*/

#include "cub3d.h"

/**
 * @brief Frees a NULL-terminated 2D array.
 *
 * @param array Pointer to the 2D array to free.
*/
void	free_2d_array(void **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

/**
 * @brief Frees dynamically allocated strings and 
 * arrays in texture info.
 *
 * @param textures Pointer to the texture info to free.
*/
static void	free_texture_info(t_texture_info *textures)
{
	if (!textures)
		return ;
	if (textures->east)
		free(textures->east);
	if (textures->north)
		free(textures->north);
	if (textures->west)
		free(textures->west);
	if (textures->south)
		free(textures->south);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

/**
 * @brief Frees the map context inside the engine.
 *
 * Closes the file descriptor if open and frees the map arrays.
 *
 * @param engine Pointer to the engine containing the map context.
*/
static void	free_map_context(t_engine *engine)
{
	if (!engine)
		return ;
	if (engine->mapinfo.fd >= 0)
		close(engine->mapinfo.fd);
	if (engine->mapinfo.file)
		free_2d_array((void **)engine->mapinfo.file);
	if (engine->map)
		free_2d_array((void **)engine->map);
}

/**
 * @brief Frees all allocated memory in the engine.
 *
 * This includes:
 * - Texture arrays and pixel buffers
 * - Texture info
 * - Map context and map
 *
 * @param engine Pointer to the engine to free.
 * @return t_status_code FAILURE (always, used for 
 * convenience in error handling)
*/
int	free_engine(t_engine *engine)
{
	if (!engine)
		return (FAILURE);
	if (engine->textures)
		free_2d_array((void **)engine->textures);
	if (engine->texture_pixels)
		free_2d_array((void **)engine->texture_pixels);
	free_texture_info(&engine->texinfo);
	free_map_context(engine);
	return (FAILURE);
}
