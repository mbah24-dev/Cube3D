/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 17:47:17 by mbah              #+#    #+#             */
/*   Updated: 2026/02/10 16:38:05 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* @file error_handler.c
 * @brief Functions for printing error messages 
 * and returning status codes.
*/

#include "cub3d.h"

/**
 * @brief Prints a formatted error message with 
 * an optional string detail.
 *
 * The message is printed to standard error in the format:
 * "cub3D: Error[: detail][: message]\n"
 *
 * @param detail Optional string providing context 
 * (e.g., filename). Can be NULL.
 * @param message Error message describing the issue. Can be NULL.
 * @param code Status code to return after printing the error.
 * @return The provided status code.
*/
int	print_error_msg(char *detail, char *message, int code)
{
	ft_putstr_fd("Error\n", 2);
	if (detail)
	{
		ft_putstr_fd(detail, 2);
		if (message)
			ft_putstr_fd(": ", 2);
	}
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}

/**
 * @brief Prints a formatted error message with 
 * an integer detail.
 *
 * The message is printed to standard error 
 * in the format:
 * "cub3D: Error: <detail>: <message>\n"
 *
 * @param detail Integer providing 
 * context (e.g., line number or index).
 * @param message Error message describing the issue. 
 * Can be NULL.
 * @param code Status code to return after printing 
 * the error.
 * @return The provided status code.
*/
int	print_error_msg_int(int detail, char *message, int code)
{
	ft_putstr_fd("Error\n", 2);
	ft_putnbr_fd(detail, 2);
	if (message)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}
