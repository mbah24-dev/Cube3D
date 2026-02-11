# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 15:26:36 by mbah              #+#    #+#              #
#    Updated: 2026/02/11 13:51:57 by mbah             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------- PHONY TARGETS ---------------------------- #
.PHONY: all re clean fclean bonus

# ------------------------- PROGRAM CONFIGURATION ----------------------- #
NAME	= cub3D
BONUS	= 0
OS_MACOS	= 0

# ------------------------- COMPILER SETTINGS --------------------------- #
CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address

# ------------------------- OS DETECTION & MLX -------------------------- #
UNAME	= $(shell uname)

ifeq ($(UNAME), Darwin)  # macOS
	MLX_PATH	= minilibx-macos/
	MLX_NAME	= libmlx.a
	MLX			= $(MLX_PATH)$(MLX_NAME)
	MLX_FLAGS	= -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
	MLX_INC		= -I$(MLX_PATH)
	OS_MACOS	= 1
else ifeq ($(UNAME), Linux)  # Linux
	MLX_PATH	= minilibx-linux/
	MLX_NAME	= libmlx.a
	MLX			= $(MLX_PATH)$(MLX_NAME)
	MLX_FLAGS	= -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
	MLX_INC		= -I$(MLX_PATH)
	OS_MACOS	= 0
else
	$(error OS not supported: $(UNAME))
endif

# ------------------------- LIBFT CONFIGURATION ------------------------- #
LIBFT_PATH	= lib/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# ------------------------- SOURCES ------------------------------------ #
SRC_PATH	= ./src/

SRC			= main.c \
			  \
			  cleanup/cleanup.c \
			  cleanup/exit_prog.c \
			  cleanup/error_handler.c \
			  \
			  initializer/init_engine.c \
			  initializer/init_mlx.c \
			  initializer/init_textures.c \
			  \
			  parser/validate_file.c \
			  parser/validate_textures.c \
			  parser/parse_file_content.c \
			  parser/parse_config.c \
			  parser/parse_colors.c \
			  parser/parse_map_layout.c \
			  parser/map_utils.c \
			  parser/map_validation.c \
			  parser/map_walls_validator.c \
			  \
			  player/init_direction.c \
			  player/input_handler.c \
			  player/player_movement.c \
			  player/movement_collision.c \
			  player/rotation.c \
			  \
			  render/mlx_image.c \
			  render/project_menu.c \
			  render/raycasting_core.c \
			  render/render_textures.c \
			  render/render_frame.c \
			  render/minimap_builder.c \
			  render/minimap_image.c \
			  \
			  debug/debug.c
			  
ifeq ($(UNAME), Darwin)
	SRC += cleanup/mlx_macos_platform.c
else ifeq ($(UNAME), Linux)
	SRC += cleanup/mlx_linux_platform.c
endif

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

# ------------------------- OBJECTS ------------------------------------ #
OBJ_PATH	= ./obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

# ------------------------- INCLUDES ----------------------------------- #
INC			= -I ./inc/ \
			  -I $(LIBFT_PATH) \
			  $(MLX_INC)

HEADERS	= ./inc/cub3d.h \
		  ./inc/linux_keys.h \
		  ./inc/macos_keys.h \
		  ./inc/types.h \
		  ./lib/libft.h

# ------------------------- BUILD RULES -------------------------------- #
all: $(OBJ_PATH) $(MLX) $(LIBFT) $(NAME)

# Create objects directories
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) \
		$(OBJ_PATH)/initializer \
		$(OBJ_PATH)/parser \
		$(OBJ_PATH)/player \
		$(OBJ_PATH)/render \
		$(OBJ_PATH)/debug \
		$(OBJ_PATH)/cleanup

# Compile object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -DOS_MACOS=$(OS_MACOS) -c $< -o $@ $(INC)

# Link program
$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) -DBONUS=$(BONUS) -DOS_MACOS=$(OS_MACOS) $(OBJS) -o $@ $(INC) $(LIBFT) $(MLX_FLAGS)

# Build libft
$(LIBFT):
	$(MAKE) -sC $(LIBFT_PATH)

# Build MLX
$(MLX):
	$(MAKE) -sC $(MLX_PATH)

# ------------------------- BONUS -------------------------------------- #
bonus:
	
	$(MAKE) all BONUS=1

# ------------------------- CLEANING ----------------------------------- #
clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all
