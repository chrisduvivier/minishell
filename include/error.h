/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:23:00 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/25 19:25:28 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define RED "\033[0;31m"
# define RESET "\033[0m"

# define ERR_MULTILINE "minishell: multiline detected !"
# define ERR_PARS_PIPE "minishell: syntax error near unexpected token `|'"
# define ERR_PARS_SEMI "minishell: syntax error near unexpected token `;'"
# define ERR_MALLOC "minishell: error while allocating memory with malloc(3)"
# define ERR_PARS_NL "minishell: syntax error near unexpected token `newline'"
# define ERR_PARS_LC "minishell: syntax error near unexpected token `<'"
# define ERR_PARS_RC "minishell: syntax error near unexpected token `>'"
# define ERR_PARS_RRC "minishell: syntax error near unexpected token `>>'"
# define SYNTAX_ERR 2
# define SIGN_C 130
# define SIGN_BSLACH 131
# define MALLOC_FAILED -100
# define CMD_EXIT_ARG_FAILURE 2
# define CMD_NOTFOUND 127

#endif