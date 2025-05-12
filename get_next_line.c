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
void	add_node_back(t_buf **head, t_buf *node);

char	*get_next_line(int fd)
{
	static t_buf	*buf_head;
	char			buffer[BUFFER_SIZE + 1];
	size_t			bytes_read;
	char			*line;
	t_buf			*temp;

	if (fd == -1)
		return (NULL);
	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
			break ;
		buffer[bytes_read] = '\0';
		temp = new_buf_node(buffer);
		add_node_back(&buf_head, temp);
		if (find_new_line(temp->buf))
		{
			line = fill_next_line(&buf_head);
			return (line);
		}
	}
	free(buf_head);
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
			i++;
		}
		temp = temp->next;
	}
	next_line_len++;
	return(next_line_len);
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
			next_line[i++] = '\n';
		to_free = temp;
		temp = temp->next;
		free(to_free->buf);
		free(to_free);
	}
	*head = temp;
	next_line[i] = '\0';
	return(next_line);
}

void	add_node_back(t_buf **head, t_buf *node)
{
	t_buf	*temp;

	if (!node)
		return ;
	temp = *head;
	if (!(*head))
		*head = node;
	else
		while ((temp))
		{
			if ((temp)->next == NULL)
			{
				(temp)->next = node;
				return ;
			}
			temp = temp->next;
		}
}
