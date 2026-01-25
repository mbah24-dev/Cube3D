/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:46:35 by mbah              #+#    #+#             */
/*   Updated: 2026/01/24 14:57:11 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file exit_prog.c
 * @brief Functions to safely exit cub3D 
 * and free allocated resources.
*/

#include "cub3d.h"

/**
 * @brief Cleans up the engine and exits the program 
 * with the given status code.
 *
 * This function:
 * - Destroys the window if it exists.
 * - Ends the MLX loop and frees the MLX context (Linux only).
 * - Frees all allocated engine data.
 * - Exits the program with the provided code.
 *
 * @param engine Pointer to the engine context.
 * @param code Exit status code.
*/
void	clean_exit(t_engine *engine, int code)
{
	if (!engine)
		exit(code);
	if (engine->win && engine->mlx)
		mlx_destroy_window(engine->mlx, engine->win);
	if (engine->mlx)
	{
		if (OS_MACOS == 0)
		{
			mlx_destroy_display(engine->mlx);
			mlx_loop_end(engine->mlx);
			free(engine->mlx);
		}
		else
		{
			free(engine->mlx);
		}
	}
	free_engine(engine);
	exit(code);
}

/**
 * @brief Convenience function to quit cub3D 
 * cleanly with success status.
 *
 * @param engine Pointer to the engine context.
 * @return Always 0.
*/
int	quit_cub3d(t_engine *engine)
{
	clean_exit(engine, SUCCESS);
	return (SUCCESS);
}
