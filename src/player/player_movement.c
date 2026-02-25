/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 15:14:28 by mbah              #+#    #+#             */
/*   Updated: 2026/01/25 15:24:36 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file player_movement.c
 * @brief Handles player movement and rotation based on input state.
 *
 * This file contains functions to move the player forward, backward, and
 * strafe left/right based on the player's current direction. It also includes
 * the main function to update the player's movement and rotation state each
 * frame based on the input received.
 */

#include "cub3d.h"

/**
 * @brief Moves the player forward in the direction they are facing.
 *
 * @param engine Pointer to the main engine structure.
 * @return 1 if the player moved, 0 otherwise.
 */
static int	move_player_forward(t_engine *engine)
{
	double	new_x;
	double	new_y;

	new_x = engine->player.pos_x + engine->player.dir_x * MOVESPEED;
	new_y = engine->player.pos_y + engine->player.dir_y * MOVESPEED;
	return (apply_player_movement(engine, new_x, new_y));
}

/**
 * @brief Moves the player backward opposite to the facing direction.
 *
 * @param engine Pointer to the main engine structure.
 * @return 1 if the player moved, 0 otherwise.
 */
static int	move_player_backward(t_engine *engine)
{
	double	new_x;
	double	new_y;

	new_x = engine->player.pos_x - engine->player.dir_x * MOVESPEED;
	new_y = engine->player.pos_y - engine->player.dir_y * MOVESPEED;
	return (apply_player_movement(engine, new_x, new_y));
}

/**
 * @brief Strafes the player to the left (perpendicular to view direction).
 *
 * @param engine Pointer to the main engine structure.
 * @return 1 if the player moved, 0 otherwise.
 */
static int	strafe_player_left(t_engine *engine)
{
	double	new_x;
	double	new_y;

	new_x = engine->player.pos_x + engine->player.dir_y * MOVESPEED;
	new_y = engine->player.pos_y - engine->player.dir_x * MOVESPEED;
	return (apply_player_movement(engine, new_x, new_y));
}

/**
 * @brief Strafes the player to the right (perpendicular to view direction).
 *
 * @param engine Pointer to the main engine structure.
 * @return 1 if the player moved, 0 otherwise.
 */
static int	strafe_player_right(t_engine *engine)
{
	double	new_x;
	double	new_y;

	new_x = engine->player.pos_x - engine->player.dir_y * MOVESPEED;
	new_y = engine->player.pos_y + engine->player.dir_x * MOVESPEED;
	return (apply_player_movement(engine, new_x, new_y));
}

/**
 * @brief Updates player movement and rotation based on input state.
 *
 * @param engine Pointer to the main engine structure.
 * @return Number of movement actions performed.
 */
int	update_player_movement(t_engine *engine)
{
	int	nb_movements;

	nb_movements = 0;
	if (engine->player.move_y == 1)
		nb_movements += move_player_forward(engine);
	if (engine->player.move_y == -1)
		nb_movements += move_player_backward(engine);
	if (engine->player.move_x == -1)
		nb_movements += strafe_player_left(engine);
	if (engine->player.move_x == 1)
		nb_movements += strafe_player_right(engine);
	if (engine->player.rotate != 0)
		nb_movements += handle_player_rotation(engine, engine->player.rotate);
	return (nb_movements);
}
