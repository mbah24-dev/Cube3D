/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:57:24 by mbah              #+#    #+#             */
/*   Updated: 2026/01/25 15:53:16 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file rotation.c
 * @brief Handles player rotation based on input state.
 *
 * This file contains functions to rotate the player's view left or right
 * by applying a 2D rotation to the player's direction and camera plane vectors.
 */

#include "cub3d.h"

/**
 * @brief Rotates the player's direction and camera plane vectors.
 *
 * Applies a 2D rotation matrix to both the direction vector and
 * the camera plane vector in order to rotate the player's view.
 *
 * @param engine Pointer to the main engine structure.
 * @param angle Rotation angle in radians.
 * @return 1 after rotation is applied.
 */
static int	rotate_player_vectors(t_engine *engine, double angle)
{
	t_player	*ply;
	double		old_x;

	ply = &engine->player;
	old_x = ply->dir_x;
	ply->dir_x = ply->dir_x * cos(angle) - ply->dir_y * sin(angle);
	ply->dir_y = old_x * sin(angle) + ply->dir_y * cos(angle);
	old_x = ply->plane_x;
	ply->plane_x = ply->plane_x * cos(angle) - ply->plane_y * sin(angle);
	ply->plane_y = old_x * sin(angle) + ply->plane_y * cos(angle);
	return (1);
}

/**
 * @brief Handles player rotation input.
 *
 * Computes the rotation angle based on rotation speed and direction,
 * then applies it to the player's vectors.
 *
 * @param engine Pointer to the main engine structure.
 * @param direction Rotation direction (-1 for left, +1 for right).
 * @return 1 if rotation occurred, 0 otherwise.
 */
int	handle_player_rotation(t_engine *engine, double direction)
{
	double	angle;

	angle = ROTSPEED * direction;
	return (rotate_player_vectors(engine, angle));
}
