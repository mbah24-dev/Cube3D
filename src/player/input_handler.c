/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:27:21 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 02:38:20 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file input_handler.c
 * @brief Handles keyboard and mouse input 
 * for player movement and rotation.
 *
 * This file contains functions to process 
 * key press and release events to update
 * the player's movement and rotation state. 
 * It also includes logic to handle
 * mouse motion for camera rotation, 
 * with horizontal wrapping to allow infinite
 * rotation without hitting window edges.
 */
#include "cub3d.h"

/**
 * @brief Handle key press events.
 *
 * Updates the player's movement and rotation state when a key is pressed.
 * No movement or rotation is applied directly here.
 *
 * @param key Pressed key code.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_key_press(int key, t_engine *engine)
{
	if (key == KEY_ESC)
		quit_cub3d(engine);
	if (key == KEY_LEFT)
		engine->player.rotate -= 1;
	if (key == KEY_RIGHT)
		engine->player.rotate += 1;
	if (key == KEY_W)
		engine->player.move_y = 1;
	if (key == KEY_A)
		engine->player.move_x = -1;
	if (key == KEY_S)
		engine->player.move_y = -1;
	if (key == KEY_D)
		engine->player.move_x = 1;
	return (0);
}

/**
 * @brief Handle key release events.
 *
 * Resets the corresponding movement or rotation state when a key is released.
 *
 * @param key Released key code.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_key_release(int key, t_engine *engine)
{
	if (key == KEY_ESC)
		quit_cub3d(engine);
	if (key == KEY_W && engine->player.move_y == 1)
		engine->player.move_y = 0;
	if (key == KEY_S && engine->player.move_y == -1)
		engine->player.move_y = 0;
	if (key == KEY_A && engine->player.move_x == -1)
		engine->player.move_x = 0;
	if (key == KEY_D && engine->player.move_x == 1)
		engine->player.move_x = 0;
	if (key == KEY_LEFT && engine->player.rotate <= 1)
		engine->player.rotate = 0;
	if (key == KEY_RIGHT && engine->player.rotate >= -1)
		engine->player.rotate = 0;
	return (0);
}

/**
 * @brief Wrap mouse position horizontally when reaching window edges.
 *
 * This allows infinite horizontal mouse movement for continuous camera rotation.
 *
 * @param engine Pointer to the main engine structure.
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 */
static void	wrap_mouse_x_position(t_engine *engine, int x, int y)
{
	if (x > engine->win_width - DIST_EDGE_MOUSE_WRAP)
	{
		x = DIST_EDGE_MOUSE_WRAP;
		mlx_move_mouse(engine, x, y);
	}
	if (x < DIST_EDGE_MOUSE_WRAP)
	{
		x = engine->win_width - DIST_EDGE_MOUSE_WRAP;
		mlx_move_mouse(engine, x, y);
	}
}

/**
 * @brief Handle mouse motion events.
 *
 * Rotates the player view depending on horizontal mouse movement.
 *
 * @param x Current mouse x position.
 * @param y Current mouse y position.
 * @param engine Pointer to the main engine structure.
 * @return Always returns 0.
 */
static int	handle_mouse_motion(int x, int y, t_engine *engine)
{
	static int	old_x = WIN_WIDTH / 2;

	wrap_mouse_x_position(engine, x, y);
	if (x == old_x)
		return (0);
	else if (x < old_x)
		engine->player.has_moved += handle_player_rotation(engine, -1);
	else if (x > old_x)
		engine->player.has_moved += handle_player_rotation(engine, 1);
	old_x = x;
	return (0);
}

/**
 * @brief Register keyboard and mouse input hooks.
 *
 * Sets up event listeners for keyboard input and optional mouse motion.
 *
 * @param engine Pointer to the main engine structure.
 */
void	register_input_hooks(t_engine *engine)
{
	mlx_hook(engine->win, EVENT_DESTROY,
		MASK_STRUCTURE_NOTIFY, quit_cub3d, engine);
	mlx_hook(engine->win, EVENT_KEY_PRESS,
		MASK_KEY_PRESS, handle_key_press, engine);
	mlx_hook(engine->win, EVENT_KEY_RELEASE,
		MASK_KEY_RELEASE, handle_key_release, engine);
	if (BONUS)
	{
		mlx_hook(engine->win, EVENT_MOUSE_MOVE,
			MASK_POINTER_MOTION, handle_mouse_motion, engine);
	}
}
