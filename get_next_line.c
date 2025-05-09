/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:25:54 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 15:26:47 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//FIXME: Remove this
#include <stdio.h>
//FIXME: Remove this

static int	find_new_line(char *line, char* left_over);
// static void	initialize_left_over(char *left_over);

char	*get_next_line(int fd)
{
	static char	left_over[BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;
	int			chars_to_trim;
	ssize_t		bytes_read;

	if (fd == -1)
		return (NULL);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0 || bytes_read == -1) // FIXME: Check this error handling
		return (NULL);
	buf[bytes_read] = '\0';
	line = ft_strjoin(left_over, buf);
	chars_to_trim = find_new_line(line, left_over);
	if (chars_to_trim >= 0)
	{
		line[ft_strlen(line) - chars_to_trim] = '\0';
		return (line);
	}
	while (bytes_read && bytes_read != -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1) // FIXME: Check this error handling
			return (NULL);
		buf[bytes_read] = '\0';
		temp = ft_strjoin(left_over, buf);
		line = ft_strjoin(line, temp);
		chars_to_trim = find_new_line(line, left_over);
		if (chars_to_trim >= 0)
		{
			line[ft_strlen(line) - chars_to_trim] = '\0';
			return (line);
		}
	}
	return (line);
}

static int	find_new_line(char *line, char* left_over)
{
	char	*new_line_char;
	int		chars_to_trim;

	new_line_char = ft_strchr(line, '\n');
	if (!new_line_char)
		return (-1);
	else
	{
		chars_to_trim = 0;
		new_line_char++;
		if (*new_line_char == '\0')
			*left_over = '\0';
		else
		{
			while (*new_line_char)
			{
				*left_over = *new_line_char;
				new_line_char++;
				left_over++;
				chars_to_trim++;
			}
		}
	}
	return (chars_to_trim);
}
