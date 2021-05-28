/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:34:11 by cduvivie          #+#    #+#             */
/*   Updated: 2021/05/28 15:54:58 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

int		get_next_line(int fd, char **line);

/*
**  helper functions
*/

char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);
char	*gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_strdup(const char *s1);
void	strjoin_gnl_helper(char **stack, int fd, char *buf);

#endif
