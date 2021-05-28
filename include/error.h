/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:23:00 by rlinkov           #+#    #+#             */
/*   Updated: 2021/04/28 15:44:45 by rlinkov          ###   ########.fr       */
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
#endif