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

static int	find_new_line(char *str);
static void	initialize_left_over(char *left_over);

char	*get_next_line(int fd)
{
	static char	left_over[BUFFER_SIZE + 1];
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd == -1)
		return (NULL);
	initialize_left_over(left_over);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0 || bytes_read == -1) // FIXME: Check this error handling
		return (NULL);
	buf[bytes_read] = '\0';
	find_new_line(buf);
	line = ft_strjoin(left_over, buf);
	return (line);
}

static int	find_new_line(char *str)
{
	int	counter;

	if (!str)
		return (0);
	counter = 0;
	while (*str)
	{
		if (*str == '\n')
			return (counter);
		counter++;
		str++;
	}
	return (counter);
}

static void	initialize_left_over(char *left_over)
{
	while (*left_over)
	{
		*left_over = '\0';
		left_over++;
	}
}
