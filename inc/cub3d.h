/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:57:03 by mbah              #+#    #+#             */
/*   Updated: 2026/02/04 01:52:48 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include "libft.h"
# include "types.h"

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>

/* ************************************************************************** */
/*                       OPERATING SYSTEM DETECTION                           */
/* ************************************************************************** */

# ifdef __APPLE__

#  include "mlx.h"
#  include <ApplicationServices/ApplicationServices.h>
#  include "macos_keys.h"
#  define OS_MACOS 1

# elif __linux__

#  include "mlx.h"
#  include <X11/keysym.h>
#  include <X11/X.h>
#  include "linux_keys.h"
#  define OS_MACOS 0

# else
#  error "Unsupported operating system"
# endif

/* ************************************************************************** */
/*                                   MACROS                                   */
/* ************************************************************************** */

# define WIN_WIDTH 1140
# define WIN_HEIGHT 780
# define TEX_SIZE 64

# ifndef DEBUG_MESSAGE
#  define DEBUG_MESSAGE 0
# endif

# ifndef BONUS
#  define BONUS 1
# endif

# ifndef OS_MACOS
#  define OS_MACOS 0
# endif

# ifndef MMAP_DEBUG_MESSAGE
#  define MMAP_DEBUG_MESSAGE 0
# endif

/**
 * @def O_DIRECTORY
 * @brief Flag used with open() to ensure the given path refers to a directory.
 *
 * This flag forces the open() system call to succeed only if the provided
 * path is a directory. If the path refers to a regular file or does not
 * exist, open() will fail.
 *
 * Some systems or environments may not define O_DIRECTORY in <fcntl.h>.
 * This conditional definition ensures portability across different
 * Unix-based operating systems.
 *
 * The value 00200000 corresponds to the official Unix/Linux definition
 * of the O_DIRECTORY flag.
*/
# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.0225
# define ROTSPEED 0.015

/**
 * @def DIST_EDGE_MOUSE_WRAP
 * @brief Threshold distance (in pixels) from the window edges 
 * used to wrap the mouse cursor.
 *
 * This value defines how close the mouse cursor can get to the window borders
 * before it is automatically repositioned (wrapped). This technique is commonly
 * used in first-person applications to allow continuous camera rotation when
 * controlling the view with the mouse.
 *
 * When the cursor position is within DIST_EDGE_MOUSE_WRAP pixels from any
 * window edge, the cursor can be moved back to a safe position (usually the
 * center of the window) to maintain smooth and uninterrupted mouse input.
 *
 * This behavior is typically used in optional or bonus features and does not
 * affect the mandatory keyboard-based controls.
*/
# define DIST_EDGE_MOUSE_WRAP 20

/* ************************************************************************** */
/*                              MINIMAP MACROS                                */
/* ************************************************************************** */

# define MINIMAP_PIXEL_SIZE 128
# define MINIMAP_VIEW_DIST 4
# define MINIMAP_COLOR_PLAYER 0xF00F0F
# define MINIMAP_COLOR_WALL 0x808080
# define MINIMAP_COLOR_FLOOR 0xE6E6E6
# define MINIMAP_COLOR_SPACE 0x404040

/* ************************************************************************** */
/*                              ERROR MESSAGES                                */
/* ************************************************************************** */

# define ERROR_USAGE \
"Usage: ./cub3D <map.cub>"

# define ERROR_FILE_NOT_CUB \
"Invalid file extension (.cub required)"

# define ERROR_FILE_NOT_XPM \
"Invalid texture extension (.xpm required)"

# define ERROR_FILE_IS_DIR \
"Path is a directory"

# define ERROR_FLOOR_CEILING \
"Invalid floor/ceiling colors"

# define ERROR_COLOR_FLOOR \
"Invalid floor color"

# define ERROR_COLOR_CEILING \
"Invalid ceiling color"

# define ERROR_INVALID_MAP \
"Invalid map"

# define ERROR_INV_LETTER \
"Invalid character in map"

# define ERROR_NUM_PLAYER \
"Multiple player positions"

# define ERROR_TEX_RGB_VAL \
"RGB value out of range (0-255)"

# define ERROR_TEX_MISSING \
"Missing texture"

# define ERROR_TEX_INVALID \
"Invalid texture"

# define ERROR_COLOR_MISSING \
"Missing color"

# define ERROR_MAP_MISSING \
"Missing map"

# define ERROR_MAP_TOO_SMALL \
"Map too small (min 3 lines)"

# define ERROR_MAP_NO_WALLS \
"Map not closed by walls"

# define ERROR_MAP_LAST \
"Map must be last in file"

# define ERROR_PLAYER_POS \
"Invalid player position"

# define ERROR_PLAYER_DIR \
"No player position found (N/S/E/W)"

# define ERROR_MALLOC \
"Malloc failed"

# define ERROR_MLX_START \
"MLX init failed"

# define ERROR_MLX_WIN \
"Window creation failed"

# define ERROR_MLX_IMG \
"Image creation failed"

/* ************************************************************************** */
/*                                      FUNCTIONS                             */
/* ************************************************************************** */

/*------------------------------ CLEANUP DIR ---------------------------------*/

/* ************************************************************************** */
/*                              CLEANUP FUNCTIONS                             */
/* ************************************************************************** */

int		free_engine(t_engine *engine);
void	free_2d_array(void **array);

/* ************************************************************************** */
/*                              ERROR_HANDLING FUNCTIONS                      */
/* ************************************************************************** */

int		print_error_msg(char *detail, char *message, int code);
int		print_error_msg_int(int detail, char *message, int code);

/* ************************************************************************** */
/*                              EXIT_PROG FUNCTIONS                           */
/* ************************************************************************** */

void	clean_exit(t_engine *engine, int code);
int		quit_cub3d(t_engine *engine);

/*----------------------------- INITIALIZER DIR ------------------------------*/

/* ************************************************************************** */
/*                              INIT_ENGINE FUNCTIONS                         */
/* ************************************************************************** */

void	init_engine(t_engine *engine);
void	init_raycast(t_raycast *ray);
void	init_image(t_image *img);

/* ************************************************************************** */
/*                              INIT_MLX FUNCTIONS                         */
/* ************************************************************************** */

void	init_image_mlx(t_engine *engine, t_image *image,
			int width, int height);
void	init_texture_image(t_engine *engine, t_image *image, char *path);
void	init_mlx(t_engine *engine);

/* ************************************************************************** */
/*                              INIT_TEXTURES FUNCTIONS                       */
/* ************************************************************************** */

void	init_texture_info(t_texture_info *texinfo);
void	init_textures(t_engine *engine);

/*------------------------------ PARSER DIR ----------------------------------*/

/* ************************************************************************** */
/*                              MAP_UTILS FUNCTIONS                           */
/* ************************************************************************** */

int		is_blank(char c);
size_t	get_max_map_line_length(t_map_context *mapinfo, int start);
int		line_contains_exactly_two_commas(char *line);

/* ************************************************************************** */
/*                              MAP_VALIDATION FUNCTIONS                      */
/* ************************************************************************** */

int		validate_map(t_engine *engine, char **map);

/* ************************************************************************** */
/*                              MAP_WALLS_VALIDATOR FUNCTIONS                 */
/* ************************************************************************** */

int		validate_map_walls(t_map_context *mapinfo, char **map);

/* ************************************************************************** */
/*                              PARSE_COLOR FUNCTIONS                         */
/* ************************************************************************** */

int		parse_floor_ceiling_color(t_engine *data,
			t_texture_info *textures, char *line, int index);

/* ************************************************************************** */
/*                              PARSE_CONFIG FUNCTIONS                        */
/* ************************************************************************** */

int		get_file_data(t_engine *data, char **file);

/* ************************************************************************** */
/*                              PARSE_FILE_CONTENT FUNCTIONS                  */
/* ************************************************************************** */

void	load_cub_file(char *path, t_engine *data);

/* ************************************************************************** */
/*                              PARSE_MAP_LAYOUT FUNCTIONS                    */
/* ************************************************************************** */

int		parse_map_layout(t_engine *data, char **file, int start);

/* ************************************************************************** */
/*                            VALIDATE_FILE FUNCTIONS                         */
/* ************************************************************************** */

int		validate_file(bool cub, char *path);

/* ************************************************************************** */
/*                              VALIDATE_TEXTURES FUNCTIONS                   */
/* ************************************************************************** */

int		validate_textures_and_colors(t_engine *engine,
			t_texture_info *textures);

/*-------------------------------- PLAYER DIR --------------------------------*/

/* ************************************************************************** */
/*                              INIT_DIRECTION FUNCTIONS                      */
/* ************************************************************************** */

void	init_player_direction_vectors(t_engine *engine);

/* ************************************************************************** */
/*                              INPUT_HANDLER FUNCTIONS                       */
/* ************************************************************************** */

void	register_input_hooks(t_engine *engine);

/* ************************************************************************** */
/*                              MOVEMENT_COLLISION FUNCTIONS                  */
/* ************************************************************************** */

int		apply_player_movement(t_engine *engine, double new_x, double new_y);

/* ************************************************************************** */
/*                              PLAYER_MOVEMENT FUNCTIONS                     */
/* ************************************************************************** */

int		update_player_movement(t_engine *engine);

/* ************************************************************************** */
/*                              ROTATION FUNCTIONS                            */
/* ************************************************************************** */

int		handle_player_rotation(t_engine *engine, double direction);

/* ************************************************************************** */
/*                              DEBUG FUNCTIONS                               */
/* ************************************************************************** */

void	debug_display_minimap(t_minimap_ctx *minimap);
void	debug_display_engine(t_engine *engine);

/* ************************************************************************** */
/*                              MLX_PLATFORM FUNCTIONS                        */
/* ************************************************************************** */

void	mlx_platform_cleanup(void *mlx);
void	mlx_center_mouse(t_engine *engine);
void	mlx_move_mouse(t_engine *engine, int x, int y);

/*-------------------------------- RENDER DIR --------------------------------*/

/* ************************************************************************** */
/*                              MINIMAP_BUILDER FUNCTIONS                     */
/* ************************************************************************** */

void	render_minimap_overlay(t_engine *engine, t_image *frame);
void	render_minimap_image_into_frame(t_engine *engine, t_image *frame,
			t_minimap_ctx *minimap);

/* ************************************************************************** */
/*                              MINIMAP_IMAGE FUNCTIONS                       */
/* ************************************************************************** */

void	render_minimap_image(t_engine *engine, t_minimap_ctx *minimap);

/* ************************************************************************** */
/*                              MLX_IMAGE FUNCTIONS                           */
/* ************************************************************************** */
void	render_3d_scene(t_engine *engine);
void	set_image_pixel(t_image *img, int color, int x, int y);

/* ************************************************************************** */
/*                           PROJECT_MENU FUNCTIONS                          */
/* ************************************************************************** */

void	draw_cub3d_menu(t_engine *engine);

/* ************************************************************************** */
/*                           RAYCASTING_CORE FUNCTIONS                        */
/* ************************************************************************** */

int		perform_raycasting(t_player *player, t_engine *engine);

/* ************************************************************************** */
/*                           RENDER_FRAME FUNCTIONS                           */
/* ************************************************************************** */

int		render(t_engine *engine);
void	render_images(t_engine *engine);

/* ************************************************************************** */
/*                           RENDER_TEXTURES FUNCTIONS                        */
/* ************************************************************************** */

void	render_wall_texture_column(t_engine *engine,
			t_texture_info *tex, t_raycast *ray, int screen_x);
void	init_texture_pixel_buffer(t_engine *engine);

#endif