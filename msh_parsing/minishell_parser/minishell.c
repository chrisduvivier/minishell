/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:50:45 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/26 17:55:36 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char	*buffer;
	char	**strs;
	int		i;
	int		ret;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (buffer == NULL)
		return (1);
	write(1, "(╯°□°)╯︵ ┻━┻$> ", 32);
	while (get_next_line(0, &buffer) > 0 && buffer != 0)
	{
		printf("commande complète : \n%s\n\n", buffer);
		clean_cmd(buffer);
		ret = syntaxe_cmd(buffer);
		//il faudra etendre les variables d'environnements
		if (ret != 0){
			strs = ft_split_msh(buffer, SEMICOLON);
			i = 0;
			while (strs[i] != NULL)
			{
                int j = 0;
				while (strs[i][j] != 0) //remplace les caractere codé par un 0
				{
					if (strs[i][j] < 0)
						strs[i][j] = '0';
					j++;
				}
				printf("coded : [\"%d\"] : |%s|\n", i, strs[i]);
				i++;
			}
		}
		write(1, "(╯°□°)╯︵ ┻━┻$> ", 32);
	}
	free(buffer);
	return (0);
}
