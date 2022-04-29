/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:37:56 by jaewkim           #+#    #+#             */
/*   Updated: 2021/08/18 16:34:21 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	chk_newline(char *str)
{
	int				idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (idx);
		++idx;
	}
	return (F_FAIL);
}

int	splited_line(char **backup, int idx_str, char **line)
{
	char			*tmp;

	(*backup)[idx_str] = '\0';
	*line = ft_strdup(*backup);
	if (!ft_strlen(&(*backup)[idx_str + 1]))
	{
		free(*backup);
		*backup = NULL;
		return (F_SUCCESS);
	}
	tmp = ft_strdup(&(*backup)[idx_str + 1]);
	free(*backup);
	*backup = tmp;
	return (F_SUCCESS);
}

int	read_after_all(char **backup, int size_read, char **line)
{
	int				idx;

	if (size_read < 0)
		return (F_FAIL);
	idx = chk_newline(*backup);
	if (*backup && idx >= 0)
		return (splited_line(backup, idx, line));
	else if (*backup)
	{
		*line = *backup;
		*backup = NULL;
		return (F_EOF);
	}
	*line = ft_strdup("");
	return (F_EOF);
}

int	get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				size_read;
	int				idx_str;

	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE <= 0))
		return (F_FAIL);
	size_read = read(fd, buf, BUFFER_SIZE);
	while (size_read > 0)
	{
		buf[size_read] = '\0';
		if (backup[fd] == NULL)
			backup[fd] = ft_strdup(buf);
		else
			backup[fd] = ft_strjoin(backup[fd], buf);
		idx_str = chk_newline(backup[fd]);
		if (idx_str >= 0)
			return (splited_line(&backup[fd], idx_str, line));
	}
	return (read_after_all(&backup[fd], size_read, line));
}
