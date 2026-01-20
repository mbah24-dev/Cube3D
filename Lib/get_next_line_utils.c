/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 15:18:07 by mbah              #+#    #+#             */
/*   Updated: 2026/01/20 03:09:03 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*allocate_zeroed_memory(size_t element_count, size_t element_size)
{
	void			*arr;
	unsigned char	*ptr;
	size_t			len;

	len = element_count * element_size;
	arr = malloc(len);
	if (arr == NULL)
		return (NULL);
	ptr = (unsigned char *)arr;
	while (len != 0)
	{
		*ptr = '\0';
		len -= 1;
		ptr += 1;
	}
	return (arr);
}

int	has_newline_in_str(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*duplicate_string(const char *original_string)
{
	int		i;
	char	*copy;

	i = 0;
	if (original_string == NULL)
		return (duplicate_string(""));
	while (original_string[i])
		i++;
	copy = allocate_zeroed_memory((i + 1), sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (original_string[i])
	{
		copy[i] = original_string[i];
		i += 1;
	}
	return (copy);
}

char	*join_strings(const char *first_string, const char *second_string)
{
	int		fst_len;
	int		snd_len;
	char	*result;

	if (!first_string && !second_string)
		return (NULL);
	fst_len = 0;
	snd_len = 0;
	while (first_string[fst_len])
		fst_len += 1;
	while (second_string[snd_len])
		snd_len += 1;
	result = allocate_zeroed_memory((fst_len + snd_len + 1), sizeof(char));
	if (result == NULL)
		return (NULL);
	fst_len = -1;
	snd_len = -1;
	while (first_string[++fst_len])
		result[fst_len] = first_string[fst_len];
	while (second_string[++snd_len])
		result[snd_len + fst_len] = second_string[snd_len];
	return (result);
}

void	free_string_pointers(char **string1, char **string2, char **string3)
{
	if (string1 && *string1)
	{
		free(*string1);
		*string1 = NULL;
	}
	if (string2 && *string2)
	{
		free(*string2);
		*string2 = NULL;
	}
	if (string3 && *string3)
	{
		free(*string3);
		*string3 = NULL;
	}
}
