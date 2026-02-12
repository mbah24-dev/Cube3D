/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:56:02 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 01:53:30 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Draw a single pixel of the final frame.
 *
 * Priority:
 * 1. Wall texture pixel (if present)
 * 2. Ceiling color (upper half)
 * 3. Floor color (lower half)
 *
 * @param engine Pointer to engine context.
 * @param frame Image being rendered.
 * @param x X screen coordinate.
 * @param y Y screen coordinate.
 */
static void	draw_frame_pixel(
	t_engine *engine, t_image *frame, int x, int y)
{
	if (engine->texture_pixels[y][x] > 0)
		set_image_pixel(frame, engine->texture_pixels[y][x], x, y);
	else if (y < engine->win_height / 2)
		set_image_pixel(frame, engine->texinfo.hex_ceiling, x, y);
	else if (y < engine->win_height - 1)
		set_image_pixel(frame, engine->texinfo.hex_floor, x, y);
}

/**
 * @brief Build and display the full frame image.
 *
 * Creates an image buffer, fills it pixel by pixel,
 * sends it to the window, then destroys it.
 *
 * @param engine Pointer to engine context.
 */
static void	present_frame(t_engine *engine, t_image *frame)
{
	if (BONUS)
		render_minimap_overlay(engine, frame);
	mlx_put_image_to_window(engine->mlx, engine->win, frame->img, 0, 0);
	mlx_destroy_image(engine->mlx, frame->img);
}

static void	render_frame_image(t_engine *engine)
{
	t_image	frame;
	int		x;
	int		y;

	frame.img = NULL;
	init_image_mlx(engine, &frame, engine->win_width,
		engine->win_height);
	y = 0;
	while (y < engine->win_height)
	{
		x = 0;
		while (x < engine->win_width)
		{
			draw_frame_pixel(engine, &frame, x, y);
			x++;
		}
		y++;
	}
	present_frame(engine, &frame);
}

/**
 * @brief Perform raycasting and render the 3D scene.
 *
 * Initializes texture buffers, casts rays,
 * then renders the resulting frame.
 *
 * @param engine Pointer to engine context.
 */
void	render_3d_scene(t_engine *engine)
{
	init_texture_pixel_buffer(engine);
	init_raycast(&engine->ray);
	perform_raycasting(&engine->player, engine);
	render_frame_image(engine);
}

/**
 * @brief Main render loop callback.
 *
 * Updates the scene only if the player has moved.
 *
 * @param engine Pointer to engine context.
 * @return Always 0.
 */
int	render(t_engine *engine)
{
	engine->player.has_moved += update_player_movement(
			engine);
	if (engine->player.has_moved == 0)
		return (0);
	render_images(engine);
	return (0);
}
