/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:32:58 by mbah              #+#    #+#             */
/*   Updated: 2026/02/10 16:40:40 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_args(char **av, t_engine *engine)
{
	if (validate_file(true, av[1]) == FAILURE)
		clean_exit(engine, FAILURE);
	load_cub_file(av[1], engine);
	if (get_file_data(engine, engine->mapinfo.file) == FAILURE)
		return (free_engine(engine));
	if (validate_map(engine, engine->map) == FAILURE)
		return (free_engine(engine));
	if (validate_textures_and_colors(engine, &engine->texinfo) == FAILURE)
		return (free_engine(engine));
	init_player_direction_vectors(engine);
	return (0);
}

int	main(int argc, char **argv)
{
	t_engine	engine;

	if (argc != 2)
		return (print_error_msg(NULL, ERROR_USAGE, FAILURE));
	init_engine(&engine);
	if (parse_args(argv, &engine) != 0)
		return (FAILURE);
	init_mlx(&engine);
	init_textures(&engine);
	render_images(&engine);
	register_input_hooks(&engine);
	mlx_loop_hook(engine.mlx, render, &engine);
	mlx_loop(engine.mlx);
	return (0);
}
