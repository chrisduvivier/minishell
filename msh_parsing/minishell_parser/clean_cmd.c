/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:13:53 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/26 16:34:23 by rlinkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_token(char c)
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
    return (0);
}

void    handle_backslash(int i, char *full_cmd, int *sq, int *dq)
{
    if (full_cmd[i - 1] != BACKSLASH) //si le précédent n'est pas un backslash
    {
        if ((*sq % 2) == 0) //si les simple quote ne sont pas ouvertes
        {
            if ((*dq % 2) == 0) //si les doubles quotes ne sont pas ouvertes
            {
                full_cmd[i] = BACKSLASH;
            }
            else if (full_cmd[i + 1] != 0) //si on est dans des doubles quotes ET que le suivant existe
            {
                if (full_cmd[i + 1] == '$' || full_cmd[i + 1] == '"') //si c'est un " ou un $
                    full_cmd[i] = BACKSLASH;
            }
        }
    }
}

void    handle_quote(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*dq % 2) == 0) //si les doubles quotes ne sont pas ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si le précédent n'est apas est un backslash
        {
            full_cmd[i] = QUOTE; //vérifier si c'est bon lorsque les single quote sont ouvertes normalement oui car l'ordre des if de check token est bon
            *sq = *sq + 1;
        }
    }
}

void    handle_dquote(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0) //si les simple quotes ne sont pas ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si le précédent n'est pas est un backslash
        {
            full_cmd[i] = DQUOTE;
            *dq = *dq + 1;
        }
    }
}

void    handle_semicolon(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq %2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[i] = SEMICOLON;
    }
}

void    handle_dollar(int i, char *full_cmd, int *sq)
{
    if ((*sq % 2) == 0) //si ni les simple quotes ne sont ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[i] = DOLLAR;
    }
}

void    handle_pipe(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq %2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[i] = PIPE;
    }
}

void    handle_lchevron(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq %2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[i] = LCHEVRON;
    }
}

void    handle_rchevron(int i, char *full_cmd, int *sq, int *dq)
{
    if ((*sq % 2) == 0 && (*dq %2) == 0) //si ni les simples ni les doubles quotes ne sont ouvertes
    {
        if (full_cmd[i - 1] != BACKSLASH) //si il n'est pas précédé par un backslash
            full_cmd[i] = RCHEVRON;
    }
}

void    check_token(int i, char *full_cmd, int *sq, int *dq)
{
    int token;
    
    token = is_token(full_cmd[i]);
    if (i == 0) //pour le premier caractere on ne peux pas se fier à son précédent
    {
        full_cmd[i] = token;
        if (token == QUOTE)
            *sq = *sq + 1;
        else if (token == DQUOTE)
            *dq = *dq + 1;
    }
    else
    {
        if (token == BACKSLASH)
            handle_backslash(i, full_cmd, sq, dq);
        else if (token == QUOTE)
            handle_quote(i, full_cmd, sq, dq);
        else if (token == DQUOTE)
            handle_dquote(i, full_cmd, sq, dq);
        else if (token == SEMICOLON)
            handle_semicolon(i, full_cmd, sq, dq);
        else if (token == DOLLAR)
            handle_dollar(i, full_cmd, sq);
        else if (token == PIPE) //au besoin on peut raccourcir le code en regroupant pipe, lchev, rchev et semicolon dans la meme fonction et en faisant fullcmd = is_token
            handle_pipe(i, full_cmd, sq, dq);
        else if (token == LCHEVRON)
            handle_lchevron(i, full_cmd, sq, dq);
        else if (token == RCHEVRON)
            handle_rchevron(i, full_cmd, sq, dq);
    }
}

void    code_cmd(char *full_cmd)
{
    int i;
    int simple_quote;
    int double_quote;

    i = 0;
    simple_quote = 0;
    double_quote = 0; 
    while(full_cmd[i] != 0)
    {
        if (is_token(full_cmd[i]) != 0) //si on trouve un caractere special
            check_token(i, full_cmd, &simple_quote, &double_quote); //alors on le regarde et on le code au besoin
        i++;
    }
}

void    clean_cmd(char *full_cmd)
{
    code_cmd(full_cmd);
}