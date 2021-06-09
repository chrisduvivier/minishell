/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:23:00 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/09 17:36:35 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define RED "\033[0;31m"
# define RESET "\033[0m"

# define ERR_MULTILINE "msh : multiline detected !"
# define ERR_PARS_PIPE "msh : syntax error near unexpected token `|'"
# define ERR_PARS_SEMI "msh : syntax error near unexpected token `;'"
# define ERR_MALLOC "msh : error while allocating memory with malloc(3)"
# define ERR_PARS_NL "msh: syntax error near unexpected token `newline'"
# define ERR_PARS_LC "msh: syntax error near unexpected token `<'"
# define ERR_PARS_RC "msh: syntax error near unexpected token `>'"
# define ERR_PARS_RRC "msh: syntax error near unexpected token `>>'"
# define SYNT_ERR 258
# define SIGN_C 130
# define SIGN_BSLACH 131
# define MALLOC_FAILED 404
# define CMD_EXIT_ARG_FAILURE 255
# define CMD_NF 127

#endif