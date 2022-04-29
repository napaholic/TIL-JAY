/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:37:56 by jaewkim           #+#    #+#             */
/*   Updated: 2021/02/21 13:23:44 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int				chk_newline_bonus(char *str)
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

int				splited_line_bonus(char **backup, int idx_str, char **line)
{
	char			*tmp;

	(*backup)[idx_str] = '\0';
	*line = ft_strdup_bonus(*backup);
	if (!ft_strlen_bonus(&(*backup)[idx_str + 1]))
	{
		free(*backup);
		*backup = NULL;
		return (F_SUCCESS);
	}
	tmp = ft_strdup_bonus(&(*backup)[idx_str + 1]);
	free(*backup);
	*backup = tmp;
	return (F_SUCCESS);
}

int				read_after_all_bonus(char **backup, int size_read, char **line)
{
	int				idx;

	if (size_read < 0)
		return (F_FAIL);
	if (*backup && (idx = chk_newline_bonus(*backup)) >= 0)
		return (splited_line_bonus(backup, idx, line));
	else if (*backup)
	{
		*line = *backup;
		*backup = NULL;
		return (F_EOF);
	}
	*line = ft_strdup_bonus("");
	return (F_EOF);
}

int				get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				size_read;
	int				idx_str;

	if ((fd < 0) || (line == NULL) || (BUFFER_SIZE <= 0))
		return (F_FAIL);
	while ((size_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[size_read] = '\0';
		if (backup[fd] == NULL)
			backup[fd] = ft_strdup_bonus(buf);
		else
			backup[fd] = ft_strjoin_bonus(backup[fd], buf);
		if ((idx_str = chk_newline_bonus(backup[fd])) >= 0)
			return (splited_line_bonus(&backup[fd], idx_str, line));
	}
	return (read_after_all_bonus(&backup[fd], size_read, line));
}
