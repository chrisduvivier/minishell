/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:50:45 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/15 18:35:04 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

int	main(void)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	write(1, "minishell$> ", 13);
	while (get_next_line(0, &buffer) > 0)
	{
		printf("cmd size : %zu\n", ft_strlen(buffer));
		printf("cmd      : %s\n", buffer);
		write(1, "minishell$> ", 13);
	}
	free(buffer);
	return (0);
}
