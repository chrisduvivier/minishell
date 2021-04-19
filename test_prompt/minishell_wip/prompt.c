/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:50:45 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/16 16:08:14 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"

//à implémenter proprement
#include "ft_split_msh.c"

int	main(void)
{
	char	*buffer;
	char	**strs;
	int		i;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	write(1, "(╯°□°)╯︵ ┻━┻$> ", 32);
	while (get_next_line(0, &buffer) > 0)
	{
		printf("cmd size : %zu\n", ft_strlen(buffer));
		printf("cmd      : %s\n", buffer);
		strs = ft_split_msh(buffer, ';');
		i = 0;
		while (strs[i] != NULL)
		{
			write(1,"XxxXX", 5);
			printf("in strs[\"%d\"] : |%s|\n", i, strs[i]);
			i++;
		}
		write(1, "(╯°□°)╯︵ ┻━┻$> ", 32);
	}
	free(buffer);
	return (0);
}
