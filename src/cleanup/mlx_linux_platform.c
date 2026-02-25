/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_linux_platform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 02:08:49 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 14:24:37 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file contains Linux-specific implementations of the MLX functions for
 * cleaning up the MLX context and handling mouse movement. */

#include "cub3d.h"

void	mlx_platform_cleanup(void *mlx)
{
	if (!mlx)
		return ;
	mlx_destroy_display(mlx);
	mlx_loop_end(mlx);
	free(mlx);
}

void	mlx_center_mouse(t_engine *engine)
{
	mlx_mouse_move(
		engine->mlx,
		engine->win,
		engine->win_width / 2,
		engine->win_height / 2);
}

void	mlx_move_mouse(t_engine *engine, int x, int y)
{
	mlx_mouse_move(engine->mlx, engine->win, x, y);
}
