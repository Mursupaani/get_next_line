/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anpollan <anpollan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:26:55 by anpollan          #+#    #+#             */
/*   Updated: 2025/05/07 15:29:24 by anpollan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//FIXME: Check inclusions
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

typedef struct s_buf
{
	char			*buf;
	struct s_buf	*next;
} t_buf;

char	*get_next_line(int fd);
t_buf	*new_buf_node(char *buf);
size_t	ft_strlen(const char *s);

#endif
