/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:07:18 by mbah              #+#    #+#             */
/*   Updated: 2026/01/22 17:20:00 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file types.h
 * @brief Definitions of core enums and structures for cub3D engine.
 */

#ifndef TYPES_H
# define TYPES_H

typedef unsigned long	t_ulong;

/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

/**
 * @enum e_status_code
 * @brief Represents generic return or control codes used throughout the engine.
 */
typedef enum e_status_code
{
	SUCCESS	= 0,
	FAILURE	= 1,
	ERR		= 2,
	BREAK	= 3,
	CONTINUE	= 4
}	t_status_code;

/**
 * @enum e_wall_direction
 * @brief Enum to index wall textures based on their orientation.
 */
typedef enum e_wall_direction
{
	NORTH	= 0,
	SOUTH	= 1,
	EAST	= 2,
	WEST	= 3
}	t_wall_direction;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

/**
 * @struct t_image
 * @brief Represents a MiniLibX image buffer.
 */
typedef struct s_image
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_image;

/**
 * @struct t_texture_info
 * @brief Stores all texture paths, colors, and mapping parameters.
 */
typedef struct s_texture_info
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texture_info;

/**
 * @struct t_minimap_ctx
 * @brief Contains all data for rendering the minimap.
 */
typedef struct s_minimap_ctx
{
	char	**map;
	t_image	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
	int		draw_off_x;
	int		draw_off_y;
}	t_minimap_ctx;

/**
 * @struct t_map_context
 * @brief Stores the map file and parsing information.
 */
typedef struct s_map_context
{
	int		fd;
	int		line_count;
	char	*path;
	char	**file;
	int		height;
	int		width;
	int		index_end_of_map;
}	t_map_context;

/**
 * @struct t_raycast
 * @brief Contains all variables used during raycasting.
 */
typedef struct s_raycast
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_raycast;

/**
 * @struct t_player
 * @brief Stores the player position, direction and movement state.
 */
typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

/**
 * @struct t_engine
 * @brief The main context of the cub3D engine containing all runtime data.
 */
typedef struct s_engine
{
	void			*mlx;
	void			*win;
	int				win_height;
	int				win_width;
	t_map_context	mapinfo;
	char			**map;
	t_player		player;
	t_raycast		ray;
	int				**texture_pixels;
	int				**textures;
	t_texture_info	texinfo;
	t_image			minimap;
}	t_engine;

#endif
