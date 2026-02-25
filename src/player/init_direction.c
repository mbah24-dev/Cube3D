/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:55:07 by mbah              #+#    #+#             */
/*   Updated: 2026/01/25 14:44:10 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file init_direction.c
 * @brief Initializes the player's direction and camera plane 
 * vectors based on the starting orientation.
 *
 * This file contains functions to set the player's 
 * initial direction and camera plane
 * vectors according to the direction character ('N', 'S', 'E', 'W') 
 * specified in the player structure. 
 * These vectors are essential for the raycasting algorithm to render
 * the 3D view correctly.
 */
#include "cub3d.h"

/**
 * @brief Initialize player direction vectors for North/South orientation.
 *
 * Sets the direction and camera plane vectors according to the
 * player's starting direction when facing North or South.
 *
 * - North: looks upward on the map
 * - South: looks downward on the map
 *
 * @param player Pointer to the player structure.
 */
static void	set_player_orientation_ns(t_player *player)
{
	if (player->dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (player->dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
}

/**
 * @brief Initialize player direction vectors for East/West orientation.
 *
 * Sets the direction and camera plane vectors according to the
 * player's starting direction when facing East or West.
 *
 * - East: looks right on the map
 * - West: looks left on the map
 *
 * @param player Pointer to the player structure.
 */
static void	set_player_orientation_ew(t_player *player)
{
	if (player->dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else if (player->dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
}

/**
 * @brief Initialize the player's direction and camera plane vectors.
 *
 * Based on the direction character stored in the player structure
 * ('N', 'S', 'E', or 'W'), this function initializes the direction
 * vector and camera plane required for raycasting.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_player_direction_vectors(t_engine *engine)
{
	set_player_orientation_ns(&engine->player);
	set_player_orientation_ew(&engine->player);
}
