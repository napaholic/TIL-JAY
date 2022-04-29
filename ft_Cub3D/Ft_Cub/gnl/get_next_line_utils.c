/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:25:10 by jaewkim           #+#    #+#             */
/*   Updated: 2021/08/18 17:10:00 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	const char *eos;

	if (str == NULL)
		return (0);
	eos = str;
	while (*eos)
		++eos;
	return (eos - str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < size)
	{
		ft_memcpy(dest, src, srclen);
		dest[srclen] = '\0';
	}
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idx;

	idx = 0;
	while (*dst && idx < dstsize)
	{
		++dst;
		++idx;
	}
	while (*src && idx + 1 < dstsize)
	{
		*dst++ = *src++;
		++idx;
	}
	if (idx < dstsize)
		*dst = '\0';
	while (*src++)
		++idx;
	return (idx);
}

char	*ft_strdup(char *s1)
{
	size_t	cnt;
	char	*str;
	size_t	i;

	cnt = ft_strlen((char *)s1);
	if ((str = (char*)malloc(sizeof(char) * cnt + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < cnt + 1)
	{
		*(unsigned char *)(str + i) = *(unsigned char *)(s1 + i);
		++i;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*result;
	size_t		s1_len;
	size_t		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if ((result = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))) == NULL)
		return (NULL);
	ft_strlcpy((char *)result, (char *)s1, s1_len + 1);
	ft_strlcat((char *)result, (char *)s2, s1_len + s2_len + 1);
	free(s1);
	s1 = NULL;
	return (result);
}
