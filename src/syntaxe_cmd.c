/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:13:41 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/08 15:40:19 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

int next_to_chevron(char *full_cmd, int i)
{
    int start_i;

    start_i = i;
    i++;
    if (!full_cmd[i])
        return (1);
    if (full_cmd[i] == RCHEVRON && full_cmd[i - 1] == RCHEVRON && full_cmd[i + 1] == RCHEVRON)
        return (5);
    while (full_cmd[i] == SPACE || full_cmd[i] == SEMICOLON)
        i++;
    if (full_cmd[i - 1] == SPACE && !full_cmd[i])
        return (1);
    if (full_cmd[i - 1] == SEMICOLON && !full_cmd[i])
        return (2);
    if (full_cmd[start_i] == LCHEVRON && full_cmd[start_i + 1] == LCHEVRON)
        return (3);
    if (full_cmd[start_i] == RCHEVRON && full_cmd[i] == LCHEVRON)
        return (3);
    if (full_cmd[start_i] == LCHEVRON && full_cmd[i] == RCHEVRON && full_cmd[i + 1] == RCHEVRON)
        return (5);
    if (full_cmd[start_i] == LCHEVRON && full_cmd[i] == RCHEVRON && full_cmd[i + 1] != RCHEVRON)
        return (4);
    return (0);
}

int syntaxe_cmd(char *full_cmd)
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
            handle_error(ERR_PARS_PIPE);
            return (0);
        }
        else if (full_cmd[i] == SEMICOLON)
        {
            handle_error(ERR_PARS_SEMI);
            return (0);
        }
    }
    while (full_cmd[i] != 0 && g_msh.status == 1)
    {
        if (full_cmd[i] == QUOTE)
            sq++;
        if (full_cmd[i] == DQUOTE)
            dq++;
        if (full_cmd[i] == PIPE)
        {
            if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == PIPE)
            {
                handle_error(ERR_PARS_PIPE);
                return (0);
            }
            if (full_cmd[i + 1] == 0)
            {
                handle_error(ERR_MULTILINE);
                return (0);
            }
            if (full_cmd[i - 1] == SEMICOLON)
            {
                handle_error(ERR_PARS_PIPE);
                return (0);
            }
        }
        if (full_cmd[i] == SEMICOLON)
        {
            if (full_cmd[i + 1] != 0 && full_cmd[i + 1] == SEMICOLON)
            {
                handle_error(ERR_PARS_SEMI);
                return (0);
            }
        }
        if (full_cmd[i] == LCHEVRON || full_cmd[i] == RCHEVRON)
        {
            if (next_to_chevron(full_cmd, i) == 1)
                handle_error(ERR_PARS_NL);
            else if (next_to_chevron(full_cmd, i) == 2)
                handle_error(ERR_PARS_SEMI);
            else if (next_to_chevron(full_cmd, i) == 3)
                handle_error(ERR_PARS_LC);
            else if (next_to_chevron(full_cmd, i) == 4)
                handle_error(ERR_PARS_RC);
            else if (next_to_chevron(full_cmd, i) == 5)
                handle_error(ERR_PARS_RRC);
        }
        i++;
    }
    if ((sq % 2) != 0 || (dq % 2) != 0)
    {
        handle_error(ERR_MULTILINE);
        return (0);
    }
    return (1);
}
