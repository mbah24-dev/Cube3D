/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:02:17 by mbah              #+#    #+#             */
/*   Updated: 2026/01/20 03:12:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	read_line_from_file(int fd, char **stash, char **temp_buffer)
{
	char	*buffer;
	int		readed;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return ;
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
		{
			free_string_pointers(stash, temp_buffer, &buffer);
			return ;
		}
		buffer[readed] = '\0';
		*temp_buffer = duplicate_string(*stash);
		free_string_pointers(stash, 0, 0);
		*stash = join_strings(*temp_buffer, buffer);
		free_string_pointers(temp_buffer, 0, 0);
		if (has_newline_in_str(*stash))
			break ;
	}
	free_string_pointers(&buffer, 0, 0);
}

char	*parse_line_content(char **stash, char **line_data)
{
	char	*line;

	*line_data = duplicate_string(*stash);
	free_string_pointers(stash, 0, 0);
	*stash = extract_after_newline(*line_data);
	line = extract_before_newline(*line_data);
	free_string_pointers(line_data, 0, 0);
	return (line);
}

char	*extract_before_newline(const char *string)
{
	int		i;
	char	*res;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (string[i] == '\n' && string[i] != '\0')
		i++;
	res = allocate_zeroed_memory((i + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		res[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		res[i] = string[i];
	return (res);
}

char	*extract_after_newline(const char *string)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	j = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (string[i] == '\n' && string[i] != '\0')
		i++;
	while (string[j])
		j++;
	res = allocate_zeroed_memory(((j - i) + 1), sizeof(char));
	j = 0;
	while (string[i + j])
	{
		res[j] = string[i + j];
		j++;
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*temp_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	temp_buffer = NULL;
	read_line_from_file(fd, &stash, &temp_buffer);
	if (stash != NULL && *stash != '\0')
		line = parse_line_content(&stash, &temp_buffer);
	if (!line || *line == '\0')
	{
		free_string_pointers(&line, &stash, &temp_buffer);
		return (NULL);
	}
	return (line);
}
