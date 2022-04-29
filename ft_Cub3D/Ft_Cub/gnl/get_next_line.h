/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:25:54 by jaewkim           #+#    #+#             */
/*   Updated: 2021/08/18 13:35:08 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define F_EOF 0
# define F_SUCCESS 1
# define F_FAIL -1

int				get_next_line(int fd, char **line);

size_t			ft_strlen(const char *str);

char			*ft_strdup(char *s1);

char			*ft_strjoin(char *s1, char *s2);
#endif