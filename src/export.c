/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:36:16 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/03 16:03:33 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void msh_bi_export(t_cmd_table t_cmd) //comment proteger les mallocs ?
{
    char    *key;
    char    *value;
    int     i;
    int     pos_equal;

    i = 0;
    if (t_cmd.argv[1][0] == DOLLAR || t_cmd.argv[1][0] == '$') //est-ce qu'on rajoute tous les cas d'erreur differents avec $ ?
    {
        handle_error("msh: export: `$': not a valid identifier");
    }
    while(i < (int)ft_strlen(t_cmd.argv[1]) && t_cmd.argv[1][i] != '=')
        i++;
    if (t_cmd.argv[1][i] != '=')
        return ;
    key = malloc(sizeof(char) * i); //i car on est sur le = donc un trop loin
    ft_strlcpy(key, t_cmd.argv[1], i + 1); //i - 1 car on ne copie pas le =
    pos_equal = i;
    i = 0;
    while (i + pos_equal < (int)ft_strlen(t_cmd.argv[1]))
        i++;
    value = malloc(sizeof(char) * i);
    ft_strlcpy(value, t_cmd.argv[1] + pos_equal + 1, i);
    if (key && key[0] == '\0' && value && value[0] != '\0')
    {
        free(key);
        printf("msh: export: `=%s': not a valid identifier", value);
        free(value);
        return ;
    }
    printf("KEY : %s | VALUE : %s\n", key, value);
    free(key);
    free(value);
}