/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:49:32 by mbah              #+#    #+#             */
/*   Updated: 2026/02/03 17:13:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Allocate and initialize the texture pixel buffer.
 *
 * This buffer stores the final rendered pixels column by column
 * before being displayed on screen.
 *
 * @param engine Pointer to the main engine structure.
 */
void	init_texture_pixel_buffer(t_engine *engine)
{
	int	i;

	if (engine->texture_pixels)
		free_2d_array((void **)engine->texture_pixels);
	engine->texture_pixels = ft_calloc(engine->win_height + 1,
			sizeof * engine->texture_pixels);
	if (!engine->texture_pixels)
		clean_exit(engine, print_error_msg(NULL, ERROR_MALLOC, FAILURE));
	i = 0;
	while (i < engine->win_height)
	{
		engine->texture_pixels[i] = ft_calloc(engine->win_width + 1,
				sizeof * engine->texture_pixels);
		if (!engine->texture_pixels[i])
			clean_exit(engine, print_error_msg(NULL, ERROR_MALLOC, FAILURE));
		i++;
	}
}

/**
 * @brief Determine which wall texture should be used for the ray hit.
 *
 * The texture depends on:
 * - the side hit by the ray (X (0) or Y (1))
 * - the ray direction
 *
 * @param engine Pointer to the engine.
 * @param ray Pointer to the current raycast data.
 */
static void	select_wall_texture(t_engine *engine, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			engine->texinfo.index = WEST;
		else
			engine->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			engine->texinfo.index = SOUTH;
		else
			engine->texinfo.index = NORTH;
	}
}

/**
 * @brief Render one vertical textured wall slice on the screen.
 *
 * This function draws a single vertical column of a wall using the correct
 * texture, based on the raycasting result.
 *
 * In a raycasting engine (like Wolfenstein 3D), the 3D scene is rendered
 * column by column. For each screen column:
 *
 * 1. A ray is cast into the map.
 * 2. The ray hits a wall.
 * 3. The wall is projected vertically on the screen.
 * 4. A vertical slice of the correct texture is drawn.
 *
 * This function performs step 4.
 *
 * ---------------------------------------------------------------------------
 * PARAMETERS
 * ---------------------------------------------------------------------------
 *
 * @param engine
 *      Pointer to the main engine structure.
 *      Contains:
 *          - win_height       : window height
 *          - textures[][]     : all loaded textures (stored as 1D arrays)
 *          - texture_pixels[][] : final screen pixel buffer
 *
 * @param tex
 *      Texture rendering helper structure.
 *      Used to compute:
 *          - size  : texture width/height (e.g., 64)
 *          - x     : horizontal coordinate in texture
 *          - y     : vertical coordinate in texture
 *          - step  : how much to move in texture per screen pixel
 *          - pos   : current vertical texture position
 *          - index : which wall texture to use (NORTH, SOUTH, EAST, WEST)
 *
 * @param ray
 *      Result of the raycasting calculation for this column.
 *      Contains:
 *          - side        : 0 = vertical wall hit, 1 = horizontal wall hit
 *          - dir_x/y     : ray direction
 *          - wall_x      : exact hit position on the wall (range [0,1])
 *          - line_height : projected wall height on screen
 *          - draw_start  : top pixel of the wall slice on screen
 *          - draw_end    : bottom pixel of the wall slice on screen
 *
 * @param screen_x
 *      The x coordinate of the screen column being drawn.
 *
 * ---------------------------------------------------------------------------
 * STEP-BY-STEP EXPLANATION
 * ---------------------------------------------------------------------------
 *
 * STEP 1 — Select the correct wall texture
 *      Depending on which side of the wall was hit (N/S/E/W),
 *      select_wall_texture() determines which texture index to use.
 *
 * STEP 2 — Compute horizontal texture coordinate (tex->x)
 *      wall_x represents where the ray hit the wall (from 0 to 1).
 *      Multiplying by texture size gives the exact X pixel in the texture.
 *
 *      Example:
 *          wall_x = 0.5
 *          size = 64
 *          → tex->x = 32
 *
 * STEP 3 — Flip texture if needed
 *      Depending on viewing direction, the texture may need to be mirrored
 *      horizontally to avoid appearing reversed.
 *
 * STEP 4 — Compute vertical texture step
 *      step = texture_size / projected_wall_height
 *
 *      This tells us how much to move inside the texture
 *      for each vertical screen pixel.
 *
 * STEP 5 — Compute initial vertical texture position
 *      Align the texture with the projected wall so it maps correctly
 *      from top to bottom.
 *
 * STEP 6 — Draw the vertical slice
 *      For each screen pixel between draw_start and draw_end:
 *
 *          1. Compute texture Y coordinate
 *          2. Fetch the color from texture
 *          3. Optionally darken certain wall sides (fake lighting)
 *          4. Write the pixel into the screen buffer
 *
 * ---------------------------------------------------------------------------
 * MENTAL MODEL
 * ---------------------------------------------------------------------------
 *
 * Imagine the screen is built from many thin vertical strips.
 *
 * For each strip:
 *      - A ray tells us which wall was hit.
 *      - We cut a vertical slice from the wall texture.
 *      - We stretch or compress that slice to match the wall height.
 *      - We paste it onto the screen column.
 *
 * The final 3D illusion is simply thousands of these textured vertical
 * slices drawn side by side.
 *
 * This function draws ONE of those slices.
 */
void	render_wall_texture_column(t_engine *engine,
			t_texture_info *tex, t_raycast *ray, int screen_x)
{
	int	y;
	int	color;

	select_wall_texture(engine, ray);
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - engine->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = engine->textures[tex->index]
		[tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			engine->texture_pixels[y][screen_x] = color;
		y++;
	}
}
