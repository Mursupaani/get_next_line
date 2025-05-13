/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:29:32 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 15:29:40 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf	*new_buf_node(char *buf)
{
	t_buf	*new;
	int		i;

	new = (t_buf *)malloc(sizeof(t_buf));
	if (!new)
		return (NULL);
	if (!buf)
		new->buf = NULL;
	else
	{
		new->buf = (char *)malloc(sizeof(char) * (ft_strlen(buf) + 1));
		i = 0;
		while (buf[i])
		{
			new->buf[i] = buf[i];
			i++;
		}
		new->buf[i] = '\0';
	}
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
	if (!new_head->buf[0])
	{
		free(new_head->buf);
		free(new_head);
	}
	else
		*head = new_head;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
