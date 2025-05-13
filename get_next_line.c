/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:25:54 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/13 15:46:35 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	find_new_line(t_buf *buffer);
char	*get_line(t_buf *head);
size_t	get_next_line_len(t_buf *head);
void	create_buf_list(t_buf **buf_head, int fd);
void	copy_line(t_buf *head, char *next_line);

char	*get_next_line(int fd)
{
	static t_buf	*buf_head;
	char			*next_line;
	ssize_t			test_read;

	test_read = read(fd, &test_read, 0);
	if (fd < 0 || BUFFER_SIZE <= 0 || test_read < 0)
		return (NULL);
	create_buf_list(&buf_head, fd);
	if (!buf_head)
		return (NULL);
	next_line = get_line(buf_head);
	store_leftover_to_head(&buf_head);
	return (next_line);
}

void	create_buf_list(t_buf **buf_head, int fd)
{
	char	*buffer;
	t_buf	*temp;
	ssize_t	bytes_read;
	bool	found_new_line;

	found_new_line = find_new_line(*buf_head);
	while (!found_new_line)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (!bytes_read)
		{
			free(buffer);
			return ;
		}
		buffer[bytes_read] = '\0';
		temp = new_buf_node(buffer);
		add_node_back(buf_head, temp);
		found_new_line = find_new_line(*buf_head);
	}
}

size_t	get_next_line_len(t_buf *head)
{
	t_buf	*temp;
	size_t	next_line_len;
	size_t	i;

	if (!head)
		return (0);
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
		if (temp->buf[i] == '\n')
		{
			next_line_len++;
			return (next_line_len);
		}
		temp = temp->next;
	}
	return (next_line_len);
}

char	*get_line(t_buf *head)
{
	char	*next_line;

	if (!head)
		return (NULL);
	next_line = (char *)malloc(sizeof(char) * (get_next_line_len(head) + 1));
	if (!next_line)
		return (NULL);
	copy_line(head, next_line);
	return (next_line);
}

void	copy_line(t_buf *head, char *next_line)
{
	t_buf	*temp;
	size_t	i;
	size_t	j;

	if (!next_line)
		return ;
	temp = head;
	i = 0;
	while (temp)
	{
		j = 0;
		while (temp->buf[j] && temp->buf[j] != '\n')
			next_line[i++] = temp->buf[j++];
		if (temp->buf[j] == '\n')
		{
			next_line[i++] = '\n';
			next_line[i] = '\0';
			return ;
		}
		temp = temp->next;
	}
	next_line[i] = '\0';
}
