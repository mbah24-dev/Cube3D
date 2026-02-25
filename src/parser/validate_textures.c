/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 16:49:06 by mbah              #+#    #+#             */
/*   Updated: 2026/01/29 17:09:37 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file validate_textures.c
 * @brief Functions to validate texture paths and RGB color values.
 */
#include "cub3d.h"

/**
 * @brief Checks whether an RGB color is valid.
 *
 * Ensures that each RGB component is within the valid range [0, 255].
 *
 * @param rgb Array of three integers representing R, G, B values.
 * @return SUCCESS if all values are valid, FAILURE otherwise.
 */
static int	validate_rgb_range(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_error_msg_int(rgb[i],
					ERROR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Converts an RGB color to a hexadecimal value.
 *
 * Each RGB component is packed into a single unsigned long
 * using the format 0xRRGGBB.
 *
 * @param rgb Array of three integers representing R, G, B values.
 * @return Hexadecimal representation of the RGB color.
 */
static unsigned long	rgb_to_hex(int *rgb)
{
	unsigned long	color;

	color = ((rgb[0] & 0xFF) << 16)
		| ((rgb[1] & 0xFF) << 8)
		| (rgb[2] & 0xFF);
	return (color);
}

/**
 * @brief Validates all texture paths and color definitions.
 *
 * This function ensures that:
 * - All wall textures (north, south, west, east) are defined
 * - Floor and ceiling colors are defined
 * - Texture files exist and are accessible
 * - RGB color values are valid
 *
 * If validation succeeds, RGB colors are converted to hexadecimal
 * and stored in the texture structure.
 *
 * @param data Pointer to the main program data structure.
 * @param textures Pointer to the texture information structure.
 * @return SUCCESS if everything is valid, FAILURE otherwise.
 */

int	validate_textures_and_colors(t_engine *engine, t_texture_info *textures)
{
	if (!textures->north || !textures->south
		|| !textures->west || !textures->east)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_TEX_MISSING, FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (print_error_msg(engine->mapinfo.path,
				ERROR_COLOR_MISSING, FAILURE));
	if (validate_file(false, textures->north) == FAILURE
		|| validate_file(false, textures->south) == FAILURE
		|| validate_file(false, textures->west) == FAILURE
		|| validate_file(false, textures->east) == FAILURE
		|| validate_rgb_range(textures->floor) == FAILURE
		|| validate_rgb_range(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = rgb_to_hex(textures->floor);
	textures->hex_ceiling = rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
