/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:48 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 17:02:27 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Load an XPM texture into a raw pixel buffer.
 *
 * This function loads an XPM file using MiniLibX, copies its pixels
 * into a newly allocated integer buffer, then destroys the temporary
 * MLX image.
 *
 * @param engine Pointer to the main engine structure.
 * @param path   Path to the XPM texture file.
 *
 * @return Pointer to the allocated pixel buffer.
 */
static int	*load_xpm_texture(t_engine *engine, char *path)
{
	t_image	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_texture_image(engine, &tmp, path);
	buffer = ft_calloc(
			engine->texinfo.size * engine->texinfo.size, sizeof(int));
	if (!buffer)
		clean_exit(engine,
			print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	y = 0;
	while (y < engine->texinfo.size)
	{
		x = 0;
		while (x < engine->texinfo.size)
		{
			buffer[y * engine->texinfo.size + x]
				= tmp.addr[y * engine->texinfo.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(engine->mlx, tmp.img);
	return (buffer);
}

/**
 * @brief Initialize all wall textures.
 *
 * Loads the NORTH, SOUTH, EAST and WEST textures defined in
 * the texture information structure and stores their pixel
 * buffers in the engine texture array.
 *
 * Texture indexing follows the e_wall_direction enum.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_textures(t_engine *engine)
{
	engine->textures = ft_calloc(5, sizeof(int *));
	if (!engine->textures)
		clean_exit(engine,
			print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	engine->textures[NORTH]
		= load_xpm_texture(engine, engine->texinfo.north);
	engine->textures[SOUTH]
		= load_xpm_texture(engine, engine->texinfo.south);
	engine->textures[EAST]
		= load_xpm_texture(engine, engine->texinfo.east);
	engine->textures[WEST]
		= load_xpm_texture(engine, engine->texinfo.west);
}

/**
 * @brief Initialize the texture information structure.
 *
 * Sets default values for texture paths, colors, and texture
 * mapping parameters.
 *
 * @param texinfo Pointer to the texture information structure.
 */
void	init_texture_info(t_texture_info *texinfo)
{
	texinfo->north = NULL;
	texinfo->south = NULL;
	texinfo->west = NULL;
	texinfo->east = NULL;
	texinfo->floor = NULL;
	texinfo->ceiling = NULL;
	texinfo->hex_floor = 0x0;
	texinfo->hex_ceiling = 0x0;
	texinfo->size = TEX_SIZE;
	texinfo->index = 0;
	texinfo->step = 0.0;
	texinfo->pos = 0.0;
	texinfo->x = 0;
	texinfo->y = 0;
}
