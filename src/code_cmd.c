/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:53 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/01 16:37:57 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_msh g_msh;

int is_token(char c)
{
    if (c == '\\')
        return (BACKSLASH);
    else if (c == '\'')
        return (QUOTE);
    else if (c == '"')
        return (DQUOTE);
    else if (c == ';')
        return (SEMICOLON);
    else if (c == '$')
        return (DOLLAR);
    else if (c == '|')
        return (PIPE);
    else if (c == '<')
        return (LCHEVRON);
    else if (c == '>')
        return (RCHEVRON);
    else if (c == ' ')
        return (SPACE);
    return (0);
}

char *handle_backslash(int *i, char *full_cmd, int *sq, int *dq)
{
    if (full_cmd[*i - 1] != BACKSLASH) //si le précédent n'est pas un backslash
    {
        if ((*sq % 2) == 0) //si les simple quote ne sont pas ouvertes
        {
            if ((*dq % 2) == 0) //si les doubles quotes ne sont pas ouvertes
            {
                full_cmd[*i] = BACKSLASH;
            }
            else if (full_cmd[*i + 1] != 0) //si on est dans des doubles quotes ET que le suivant existe
            {
                if (full_cmd[*i + 1] == '$' || full_cmd[*i + 1] == '"') //si c'est un " ou un $
                    full_cmd[*i] = BACKSLASH;
            }
        }
    }
    return (full_cmd);
}

char *handle_quote(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*dq % 2) == 0) //si les doubles quotes ne sont pas ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si le précédent n'est apas est un backslash
        {
            full_cmd[*i] = QUOTE; //vérifier si c'est bon lorsque les single quote sont ouvertes normalement oui car l'ordre des if de check token est bon
            *sq = *sq + 1;
        }
    }
    return (full_cmd);
}

char *handle_dquote(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0) //si les simple quotes ne sont pas ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si le précédent n'est pas est un backslash
        {
            full_cmd[*i] = DQUOTE;
            *dq = *dq + 1;
        }
    }
    return (full_cmd);
}

char *handle_semicolon(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq % 2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[*i] = SEMICOLON;
    }
    return (full_cmd);
}

/*
** Unlike the other functions, this one not only subsitute $ token by an non printable char
** but is substitute $ token with the corresponding environment variable if it exist
*/

char *handle_dollar(int *i, char *full_cmd, int *sq)
{
    if ((*sq % 2) == 0) //si ni les simple quotes ne sont ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
        {
            if (full_cmd[*i + 1] && full_cmd[*i + 1] != ' ')
            {
                full_cmd[*i] = DOLLAR;
                full_cmd = set_env_var(full_cmd, i);
            }
        }
    }
    return (full_cmd);
}

char *handle_pipe(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq % 2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[*i] = PIPE;
    }
    return (full_cmd);
}

char *handle_lchevron(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq % 2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[*i] = LCHEVRON;
    }
    return (full_cmd);
}

char *handle_rchevron(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq % 2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[*i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[*i] = RCHEVRON;
    }
    return (full_cmd);
}

char *handle_space(int *i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq % 2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        full_cmd[*i] = SPACE; //nous permet de différencier les espaces servant a separer les cmd et leurs arguments des espaces literal
    }
    return (full_cmd);
}

char *check_token(int *i, char *full_cmd, int *sq, int *dq)
{
    int token;
    token = is_token(full_cmd[*i]);
    if (*i == 0) //pour le premier caractere on ne peux pas se fier à son précédent
    {
        full_cmd[*i] = token;
        if (token == QUOTE)
            *sq = *sq + 1;
        else if (token == DQUOTE)
            *dq = *dq + 1;
        else if (token == DOLLAR && (full_cmd[*i + 1] != ' ' && full_cmd[*i + 1]))
            full_cmd = set_env_var(full_cmd, i);
        else if (token == DOLLAR && (full_cmd[*i + 1] == ' ' || !full_cmd[*i + 1]))
            full_cmd[*i] = '$';
    }
    else
    {
        if (token == BACKSLASH)
            full_cmd = handle_backslash(i, full_cmd, sq, dq);
        else if (token == QUOTE)
            full_cmd = handle_quote(i, full_cmd, sq, dq);
        else if (token == DQUOTE)
            full_cmd = handle_dquote(i, full_cmd, sq, dq);
        else if (token == SEMICOLON)
            full_cmd = handle_semicolon(i, full_cmd, sq, dq);
        else if (token == DOLLAR)
            full_cmd = handle_dollar(i, full_cmd, sq);
        else if (token == PIPE) //au besoin on peut raccourcir le code en regroupant pipe, lchev, rchev et semicolon dans la meme fonction et en faisant fullcmd = is_token
            full_cmd = handle_pipe(i, full_cmd, sq, dq);
        else if (token == LCHEVRON)
            full_cmd = handle_lchevron(i, full_cmd, sq, dq);
        else if (token == RCHEVRON)
            full_cmd = handle_rchevron(i, full_cmd, sq, dq);
        else if (token == SPACE)
            full_cmd = handle_space(i, full_cmd, sq, dq);
    }
    return (full_cmd);
}

char *code_cmd(char *full_cmd)
{
    int i;
    int simple_quote;
    int double_quote;

    i = 0;
    simple_quote = 0;
    double_quote = 0;
    while (full_cmd[i] != 0)
    {
        if (is_token(full_cmd[i]) != 0)                                        //si on trouve un caractere special
            full_cmd = check_token(&i, full_cmd, &simple_quote, &double_quote); //alors on le regarde et on le code au besoin
        i++;
    }
    return (full_cmd);
}
