/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaewkim <jaewkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 12:25:54 by jaewkim           #+#    #+#             */
/*   Updated: 2021/02/21 13:17:44 by jaewkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# define F_EOF 0
# define F_SUCCESS 1
# define F_FAIL -1

int				get_next_line(int fd, char **line);

size_t			ft_strlen_bonus(const char *str);

char			*ft_strdup_bonus(const char *s1);

char			*ft_strjoin_bonus(char *s1, char *s2);
#endif
