/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:25:10 by jaewkim           #+#    #+#             */
/*   Updated: 2021/02/21 13:23:43 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_bonus(const char *str)
{
	const char *eos;

	if (str == NULL)
		return (0);
	eos = str;
	while (*eos)
		++eos;
	return (eos - str);
}

size_t	ft_strlcpy_bonus(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			cnt;

	if (!dst || !src)
		return (0);
	i = ft_strlen_bonus(src);
	cnt = 0;
	if (dstsize == 0)
		return (i);
	while ((cnt < i) && (cnt < dstsize - 1))
	{
		dst[cnt] = src[cnt];
		++cnt;
	}
	dst[cnt] = '\0';
	return (i);
}

size_t	ft_strlcat_bonus(char *dst, const char *src, size_t dstsize)
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

char	*ft_strdup_bonus(const char *s1)
{
	size_t	cnt;
	char	*str;
	size_t	i;

	cnt = ft_strlen_bonus((char *)s1);
	if ((str = (char*)malloc(sizeof(*s1) * (cnt + 1))) == NULL)
		return (NULL);
	i = 0;
	while (i < cnt + 1)
	{
		*(unsigned char *)(str + i) = *(unsigned char *)(s1 + i);
		++i;
	}
	return (str);
}

char	*ft_strjoin_bonus(char *s1, char *s2)
{
	char		*result;
	size_t		s1_len;
	size_t		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen_bonus(s1);
	s2_len = ft_strlen_bonus(s2);
	if ((result = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))) == NULL)
		return (NULL);
	ft_strlcpy_bonus((char *)result, (char *)s1, s1_len + 1);
	ft_strlcat_bonus((char *)result, (char *)s2, s1_len + s2_len + 1);
	free(s1);
	s1 = NULL;
	return (result);
}
