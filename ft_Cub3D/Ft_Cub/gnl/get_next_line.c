/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 06:23:51 by yeju              #+#    #+#             */
/*   Updated: 2021/09/18 08:01:14 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_split(char **string, char **line, int i)
{
	char	*tmp;
	int		len;

	(*string)[i] = '\0';
	*line = ft_strdup(*string);
	len = ft_strlen_gnl(*string + i + 1);
	if (len == 0)
	{
		free(*string);
		*string = 0;
		return (1);
	}
	tmp = ft_strdup(*string + i + 1);
	free(*string);
	*string = tmp;
	return (1);
}

int	return_this(char **string, char **line, int read_size)
{
	int	i;

	if (read_size < 0)
		return (-1);
	i = ft_strchr(*string);
	if (*string && i >= 0)
		return (gnl_split(string, line, i));
	else if (*string)
	{
		*line = *string;
		*string = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*string[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	int			read_size;
	int			i;

	if ((fd < 0) || (OPEN_MAX < fd) || (!line) || (BUFFER_SIZE <= 0))
		return (-1);
	read_size = 1;
	while (read_size > 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 0)
			break ;
		buffer[read_size] = '\0';
		string[fd] = ft_strjoin(string[fd], buffer);
		i = ft_strchr(string[fd]);
		if (i >= 0)
			return (gnl_split(&string[fd], line, i));
	}
	return (return_this(&string[fd], line, read_size));
}
