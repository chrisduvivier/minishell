/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:13:41 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/08 19:23:15 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int syntaxe_cmd(t_msh *msh, char *full_cmd)
{
    int sq;
    int dq;
    int i;

    i = 0;
    sq = 0;
    dq = 0;
    if (i == 0)
    {
        if (full_cmd[i] == PIPE)
        {
            handle_error(msh, ERR_PARS_PIPE);
            return (0);
        }
        else if (full_cmd[i] == SEMICOLON)
        {
            handle_error(msh, ERR_PARS_SEMI);
            return (0);
        }
    }
    while (full_cmd[i] != 0)
    {
        if (full_cmd[i] == QUOTE)
            sq++;
        if (full_cmd[i] == DQUOTE)
            dq++;
        if (full_cmd[i] == PIPE)
        {
            write(1,"HERE\n", 5);
            printf("ERR !:X%cX\n", full_cmd[i + 1]);
            if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == PIPE)
            {
                write(1,"HEREP\n", 6);
                handle_error(msh, ERR_PARS_PIPE);
                return (0);
            }
            printf("ERR !:X%cX\n", full_cmd[i + 1]);
            if (full_cmd[i + 1] == 0)
            {
                write(1,"HERE0\n", 6);
                printf("ERR ?:X%cX\n", full_cmd[i + 1]);
                handle_error(msh, ERR_MULTILINE);
                return (0);
            }
            if (full_cmd[i - 1] == SEMICOLON)
            {
                handle_error(msh, ERR_PARS_PIPE);
                return (0);
            }
        }
        if ( full_cmd[i] == SEMICOLON)
        {
            if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == SEMICOLON)
            {
                handle_error(msh, ERR_PARS_SEMI);
                return (0);
            }            
        }
        //rajouter check erreurs de chevrons <, <<, <<<, >, >>
        i++;
    }
    if ((sq % 2) != 0 || (dq % 2) != 0)
    {
        handle_error(msh, ERR_MULTILINE);
        return (0);
    }
    return (1);
}