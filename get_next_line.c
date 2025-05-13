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
#include <stddef.h>
#include <stdio.h>
//FIXME: Remove this

bool	find_new_line(char *buffer);
char	*fill_next_line(t_buf **head);
size_t	get_next_line_len(t_buf *head);
t_buf	*store_leftover_to_head(t_buf *head);

char	*get_next_line(int fd)
{
	static t_buf	*buf_head;
	char			buffer[BUFFER_SIZE + 1];
	size_t			bytes_read;
	t_buf			*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buf_head)
	{
		if (find_new_line(buf_head->buf))
			return (fill_next_line(&buf_head));
	}
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		temp = new_buf_node(buffer);
		add_node_back(&buf_head, temp);
		if (find_new_line(temp->buf))
			return (fill_next_line(&buf_head));
	}
	free_list(buf_head);
	return (NULL);
}

bool	find_new_line(char *buffer)
{
	while (*buffer)
	{
		if (*buffer == '\n')
			return (true);
		buffer++;
	}
	return (false);
}

size_t	get_next_line_len(t_buf *head)
{
	t_buf	*temp;
	size_t	next_line_len;
	size_t	i;

	next_line_len = 0;
	temp = head;
	while (temp)
	{
		i = 0;
		while (temp->buf[i] && temp->buf[i] != '\n')
		{
			next_line_len++;
			if (temp->buf[i] == '\n')
				next_line_len++;
			i++;
		}
		temp = temp->next;
	}
	return (next_line_len);
}

char	*fill_next_line(t_buf **head)
{
	char	*next_line;
	t_buf	*temp;
	t_buf	*to_free;
	size_t	i;
	size_t	j;

	next_line = (char *)malloc(sizeof(char) * (get_next_line_len(*head) + 1));
	if (!next_line)
		return (NULL);
	temp = *head;
	i = 0;
	while (temp)
	{
		j = 0;
		while (temp->buf[j] && temp->buf[j] != '\n')
			next_line[i++] = temp->buf[j++];
		if (temp->buf[j] == '\n')
		{
			next_line[i++] = '\n';
			*head = store_leftover_to_head(temp);
		}
		to_free = temp;
		temp = temp->next;
		free(to_free->buf);
		free(to_free);
	}
	next_line[i] = '\0';
	return (next_line);
}

t_buf	*store_leftover_to_head(t_buf *head)
{
	t_buf	*temp;
	t_buf	*new_head;
	size_t	i;

	temp = head;
	i = 0;
	while (temp->buf[i])
	{
		if (temp->buf[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	new_head = new_buf_node(&(temp->buf[i]));
	return (new_head);
}
