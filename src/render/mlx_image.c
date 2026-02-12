/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:34:15 by mbah              #+#    #+#             */
/*   Updated: 2026/01/31 23:37:09 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_image_pixel(t_image *img, int color, int x, int y)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

/**
 * @brief Render all visible elements.
 *
 * Includes the 3D scene and bonus elements if enabled.
 *
 * @param engine Pointer to engine context.
 */
void	render_images(t_engine *engine)
{
	render_3d_scene(engine);
	if (BONUS)
	{
		draw_cub3d_menu(engine);
	}
}
