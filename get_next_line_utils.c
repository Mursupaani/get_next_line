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
