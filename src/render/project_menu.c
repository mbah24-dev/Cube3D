/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:46:23 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 02:01:04 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_menu_background(t_engine *engine, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_pixel_put(engine->mlx, engine->win, x, y, 0x444444);
			x++;
		}
		y++;
	}
}

static void	draw_macos_cub3d_menu(t_engine *engine)
{
	int	x;
	int	y;

	x = 10;
	y = 10;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "CUB3D CONTROLS (macOS)");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "W / Z : Move forward");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "S     : Move backward");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "A / Q : Strafe left");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "D     : Strafe right");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "<- / -> : Rotate camera");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "ESC   : Exit");
}

static void	draw_linux_cub3d_menu(t_engine *engine)
{
	int	x;
	int	y;

	x = 10;
	y = 10;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "CUB3D CONTROLS (Linux)");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "W     : Move forward");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "S     : Move backward");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "A     : Strafe left");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "D     : Strafe right");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "<- / -> : Rotate camera");
	y += 20;
	mlx_string_put(engine->mlx, engine->win, x, y,
		0xFFFFF0, "ESC   : Exit");
}

void	draw_cub3d_menu(t_engine *engine)
{
	draw_menu_background(engine, 300, 160);
	if (OS_MACOS)
		draw_macos_cub3d_menu(engine);
	else
		draw_linux_cub3d_menu(engine);
}
