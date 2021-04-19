/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:34:15 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:07:36 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	- Description:
**	exit function which checks if freeing the stack[fd] is needed
**	before returning (-1).
*/

static int	free_and_exit(char **fd_str)
{
	if (fd_str && *fd_str)
	{
		free(*fd_str);
		*fd_str = NULL;
	}
	return (-1);
}

/*
**	- Description:
**	Append the `\n` or `\0` terminating string to line.
**	while doing so, store the excessive reading to the static memory.
**	ex:
**		"Hello, World!\n how are you?\0"
**		|    line    |     excess     |
**
**	=> stack[fd] = "how are you?\0"
**
**	If it reached EOF, simply duplicate the line and free the stack, return 0.
**	If malloc fails in any of the helper function, free(str[fd]) & return -1.
*/

static int	append_line(char **fd_str, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while ((*fd_str)[len] != '\0' && (*fd_str)[len] != '\n')
		len++;
	if ((*fd_str)[len] == '\n')
	{
		*line = gnl_ft_substr(*fd_str, 0, len);
		tmp = gnl_ft_strdup(&((*fd_str)[len + 1]));
		free(*fd_str);
		*fd_str = tmp;
		if (!(*line) || !(*fd_str))
			return (free_and_exit(fd_str));
		return (1);
	}
	*line = gnl_ft_strdup(*fd_str);
	free(*fd_str);
	*fd_str = NULL;
	if (*line == NULL)
		return (free_and_exit(fd_str));
	return (0);
}

/*
**	- Description:
**	Handles the output value of gnl.
**	`-1` If the read cursor got a negative value (read failed).
**	If the cursor reached EOF and the stack is empty,
**	we return 0 with an empty line.
**	Otherwise, we call append_line and returns its returned value.
**
**	If malloc fails in any of the helper function, free(str[fd]) & return -1.
*/

static int	output(int cursor, char **stack, int fd, char **line)
{
	if (cursor == 0 && (!stack[fd]))
	{
		*line = gnl_ft_strdup("");
		if (!(*line))
			return (free_and_exit(&stack[fd]));
		return (0);
	}
	return (append_line(&stack[fd], line));
}

/*
**	- Description:
**	ft_read_gnl keeps what it reads on the stack (static char), and
**	extract the line once a `\n` or `\0` is found. If the stack[fd] exists,
**	which means the previous read call had more char after the `\n`, we join
**	them together.
**
**	- Return value:
**	cursor upon successful reading and memory allocation.
**	Otherwise, return (-1).
*/

static int	ft_read_gnl(char **stack, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;
	int		cursor;

	cursor = 0;
	while (!(gnl_ft_strchr(stack[fd], '\n'))
		&& (cursor = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[cursor] = '\0';
		if (!stack[fd])
		{
			stack[fd] = gnl_ft_strdup(buf);
			if (!stack[fd])
				return (-1);
		}
		else
		{
			tmp = ft_strjoin(stack[fd], buf);
			free(stack[fd]);
			stack[fd] = tmp;
			if (!stack[fd])
				return (-1);
		}
	}
	return (cursor);
}

/*
**	- Description:
**	Write a function which returns a line read from a fd, without the newline.
**	If a memory allocation fails at any point, we return -1.
**
**	- Return value:
**	1 : a line has been read.
**	0 : EOF has been reached.
**	-1 : An error happened.
**
**	- Error handling:
**	Once a malloc or read fails, we call free_and_exit to free the stack[fd].
**	Note that this will free only the stack[fd] which gave error.
*/

int	get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	int			cursor;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE < 1)
		return (-1);
	cursor = ft_read_gnl(stack, fd);
	if (cursor < 0)
		return (free_and_exit(&stack[fd]));
	return (output(cursor, stack, fd, line));
}
