/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:44:07 by mbah              #+#    #+#             */
/*   Updated: 2026/01/25 14:57:28 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file movement_collision.c
 * @brief Handles player movement with collision detection 
 * against walls and map boundaries.
 *
 * This file contains functions to validate player movement 
 * by checking for wall collisions and ensuring the player 
 * stays within the map boundaries. 
 * The logic differs based on whether the BONUS mode is enabled,
 * allowing for more precise
 * collision detection in the bonus version of the project.
 */

#include "cub3d.h"

/**
 * @brief Checks whether a map cell is walkable (no wall collision).
 *
 * This function verifies that the target position corresponds to an empty
 * floor tile ('0') in the map grid.
 *
 * @param engine Pointer to the main engine structure.
 * @param x Target x-coordinate in world space.
 * @param y Target y-coordinate in world space.
 * @return true if the tile is walkable, false otherwise.
 */
static bool	is_walkable_tile(t_engine *engine, double x, double y)
{
	if (engine->map[(int)y][(int)x] == '0')
		return (true);
	return (false);
}

/**
 * @brief Checks whether a position lies inside the playable map boundaries.
 *
 * A small margin is applied to prevent the player from getting too close
 * to the edges, avoiding out-of-bounds access and rendering issues.
 *
 * @param engine Pointer to the main engine structure.
 * @param x Target x-coordinate.
 * @param y Target y-coordinate.
 * @return true if the position is inside map bounds, false otherwise.
 */
static bool	is_inside_map_bounds(t_engine *engine, double x, double y)
{
	if (x < 0.25 || x >= engine->mapinfo.width - 1.25)
		return (false);
	if (y < 0.25 || y >= engine->mapinfo.height - 0.25)
		return (false);
	return (true);
}

/**
 * @brief Determines whether the player can move to a given position.
 *
 * The validation logic depends on the compilation mode:
 * - Mandatory: only map bounds are checked.
 * - Bonus: wall collision is checked instead.
 *
 * @param engine Pointer to the main engine structure.
 * @param x Target x-coordinate.
 * @param y Target y-coordinate.
 * @return true if movement is allowed, false otherwise.
 */
static bool	can_move_to_position(t_engine *engine, double x, double y)
{
	if (!BONUS && is_inside_map_bounds(engine, x, y))
		return (true);
	if (BONUS && is_walkable_tile(engine, x, y))
		return (true);
	return (false);
}

/**
 * @brief Applies player movement while handling collisions.
 *
 * The function independently validates movement on the X and Y axes,
 * allowing smooth sliding along walls.
 *
 * @param engine Pointer to the main engine structure.
 * @param new_x Candidate x-position.
 * @param new_y Candidate y-position.
 * @return 1 if the player moved, 0 otherwise.
 */
int	apply_player_movement(t_engine *engine, double new_x, double new_y)
{
	int	ret;

	ret = 0;
	if (can_move_to_position(engine, new_x, engine->player.pos_y))
	{
		engine->player.pos_x = new_x;
		ret = 1;
	}
	if (can_move_to_position(engine, engine->player.pos_x, new_y))
	{
		engine->player.pos_y = new_y;
		ret = 1;
	}
	return (ret);
}
