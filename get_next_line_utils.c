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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret_str;
	size_t	tot_len;

	if (!s1 || !s2)
		return (NULL);
	tot_len = ft_strlen(s1) + ft_strlen(s2);
	ret_str = (char *)malloc(sizeof(char) * tot_len + 1);
	if (!ret_str)
		return (NULL);
	ft_strlcpy(ret_str, s1, tot_len + 1);
	ft_strlcat(ret_str, s2, tot_len + 1);
	return (ret_str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	src_size = 0;
	while (*(src + src_size))
		src_size++;
	if (size == 0)
		return (src_size);
	i = 0;
	while (*(src + i) && i < size - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (src_size);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = dst_len;
	j = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[j])
		{
			dst[i++] = src[j++];
		}
		dst[i] = '\0';
	}
	if (dst_len >= size)
		dst_len = size;
	return (dst_len + src_len);
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
