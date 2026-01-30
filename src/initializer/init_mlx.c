/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:24:51 by mbah              #+#    #+#             */
/*   Updated: 2026/01/30 17:02:24 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialize a MiniLibX image structure.
 *
 * Creates a new MLX image with the given dimensions and retrieves
 * its pixel buffer information.
 *
 * @param engine Pointer to the main engine structure.
 * @param image  Pointer to the image structure to initialize.
 * @param width  Image width in pixels.
 * @param height Image height in pixels.
 */
void	init_image_mlx(t_engine *engine, t_image *image,
						int width, int height)
{
	init_image(image);
	image->img = mlx_new_image(engine->mlx, width, height);
	if (!image->img)
		clean_exit(engine,
			print_error_msg("mlx", ERROR_MLX_IMG, FAILURE));
	image->addr = (int *)mlx_get_data_addr(
			image->img,
			&image->pixel_bits,
			&image->size_line,
			&image->endian);
}

/**
 * @brief Load a texture image from an XPM file.
 *
 * Loads an XPM texture using MiniLibX and stores the pixel data
 * in the provided image structure.
 *
 * @param engine Pointer to the main engine structure.
 * @param image  Pointer to the image structure to initialize.
 * @param path   Path to the XPM texture file.
 */
void	init_texture_image(t_engine *engine, t_image *image, char *path)
{
	init_image(image);
	image->img = mlx_xpm_file_to_image(
			engine->mlx,
			path,
			&engine->texinfo.size,
			&engine->texinfo.size);
	if (!image->img)
		clean_exit(engine,
			print_error_msg("mlx", ERROR_MLX_IMG, FAILURE));
	image->addr = (int *)mlx_get_data_addr(
			image->img,
			&image->pixel_bits,
			&image->size_line,
			&image->endian);
}

/**
 * @brief Initialize MiniLibX and create the main window.
 *
 * Starts the MLX context, creates the main rendering window,
 * and applies bonus-related initializations when enabled.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_mlx(t_engine *engine)
{
	engine->mlx = mlx_init();
	if (!engine->mlx)
		clean_exit(engine,
			print_error_msg("mlx", ERROR_MLX_START, FAILURE));
	engine->win_width = WIN_WIDTH;
	engine->win_height = WIN_HEIGHT;
	engine->win = mlx_new_window(
			engine->mlx,
			engine->win_width,
			engine->win_height,
			"Cub3D - mbah");
	if (!engine->win)
		clean_exit(engine,
			print_error_msg("mlx", ERROR_MLX_WIN, FAILURE));
	if (BONUS)
	{
		if (!OS_MACOS)
		{
			mlx_mouse_move(
				engine->mlx,
				engine->win,
				engine->win_width / 2,
				engine->win_height / 2);
		}
	}
}
