/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 06:23:43 by yeju              #+#    #+#             */
/*   Updated: 2021/09/18 07:58:51 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	len;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
	{
		return (src_len);
	}
	len = 0;
	while (src[len] != '\0' && len < (dstsize - 1))
	{
		dest[len] = src[len];
		len++;
	}
	dest[len] = 0;
	return (src_len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	dest_len;
	size_t	src_len;

	dest_len = ft_strlen_gnl(dest);
	src_len = ft_strlen_gnl(src);
	len = 0;
	while (src[len] != '\0' && dest_len + 1 + len < dstsize)
	{
		dest[dest_len + len] = src[len];
		len++;
	}
	dest[dest_len + len] = '\0';
	if (dstsize < dest_len)
		return (dstsize + src_len);
	return (dest_len + src_len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*string;
	int		s1_len;
	int		s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
	{
		if (s1)
			return (ft_strdup(s1));
		return (ft_strdup(s2));
	}
	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	string = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!string)
		return (NULL);
	ft_strlcpy(string, s1, s1_len + 1);
	free(s1);
	ft_strlcat(string + (s1_len), s2, s2_len + 1);
	return (string);
}

char	*ft_strdup(char *s1)
{
	char	*new_str;
	int		len;
	int		i;

	len = ft_strlen_gnl(s1);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
