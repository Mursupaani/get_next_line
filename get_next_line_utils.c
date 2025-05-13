/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/13 15:46:41 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf	*new_buf_node(char *buf)
{
	t_buf	*new;

	new = (t_buf *)malloc(sizeof(t_buf));
	if (!new)
		return (NULL);
	if (!buf)
		new->buf = NULL;
	else
		new->buf = buf;
	new->next = NULL;
	return (new);
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
	{
		while (temp)
		{
			if ((temp)->next == NULL)
			{
				(temp)->next = node;
				return ;
			}
			temp = temp->next;
		}
	}
}

void	free_list(t_buf **head, t_buf *new_head)
{
	t_buf	*temp;

	if (*head == NULL)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		free((*head)->buf);
		free(*head);
		*head = temp;
	}
	*head = NULL;
	if (new_head && new_head->buf && !new_head->buf[0])
	{
		free(new_head->buf);
		free(new_head);
	}
	else
		*head = new_head;
}

bool	find_new_line(t_buf *buf_head)
{
	int	i;

	while (buf_head)
	{
		i = 0;
		while (buf_head->buf[i])
		{
			if (buf_head->buf[i] == '\n')
				return (true);
			i++;
		}
		buf_head = buf_head->next;
	}
	return (false);
}

t_buf	*store_leftover_to_head(t_buf **head)
{
	t_buf	*new_head;
	t_buf	*last_node;
	char	*buf_remainder;
	size_t	i;
	size_t	j;

	buf_remainder = (char *)malloc(BUFFER_SIZE + 1);
	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
	i = 0;
	j = 0;
	while (last_node->buf[i])
	{
		if (last_node->buf[i] == '\n')
		{
			i++;
			while (last_node->buf[i])
				buf_remainder[j] = last_node->buf[i];
			break ;
		}
		i++;
	}
	new_head = new_buf_node(buf_remainder);
	free_list(head, new_head);
	return (new_head);
}
