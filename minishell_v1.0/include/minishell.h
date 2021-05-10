/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:43:58 by rlinkov           #+#    #+#             */
/*   Updated: 2021/05/10 18:58:53 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>


# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "error.h"

/*
**	struct for organizing data needed to execute commands
**	Description:
**	- command: holds core command ("cd", "echo", "pwd")
**	- option: option to cmd if any ("-n")
**	- arg: arguments of the cmd ("This is a string", "output.txt")
**	- in_file: name of input file name (NOT SURE IF ACTUALLY NEEDED)
**	- out_file: name of output file name (NOT SURE IF ACTUALLY NEEDED)
**	- in_file_fd: file descriptor of input (STD_IN as default)
**	- out_file_fd: file descriptor of output. This could be a new file (STD_OUT as default)
**	- err_file_fd: file descriptor of error (STD_ERR as default)
**	- next: pointer to next cmd
*/
typedef struct s_cmd_table {
	char				*origin_cmd;
	char 				*cmd;
	char 				*opt;
	char 				*arg;
	char 				*in_file;
	char 				*out_file;
	int 				in_file_fd;
	int 				out_file_fd;
	int 				err_file_fd;
	struct s_cmd_table	*next;
}						t_cmd_table;

/*
** Core struct which carries data of the minishell. 
*/
typedef struct s_msh {
	int				status;
	t_cmd_table		*cmd_t;
}				t_msh;

//TOKEN
# define BACKSLASH -1
# define QUOTE -2
# define DQUOTE -3
# define SEMICOLON -4
# define DOLLAR -5
# define PIPE -6
# define LCHEVRON -7
# define RCHEVRON -8
# define SPACERM -9
# define SPACE -10

# define NEW_COMMAND_PROMPT "(╯°□°)╯︵ ┻━┻$> "

void	prompt(t_msh *msh);
void    get_cmd(char **str);
void	handle_error(t_msh *msh, char *err_tag);
char	**ft_split_msh(char const *s, char c);
void    code_cmd(char *str);
int		syntaxe_cmd(t_msh *msh, char *full_cmd);
char    *remove_space(t_msh *msh, char *full_cmd);
char    *clean_cmd(t_msh *msh, char *str);
int     exec_cmd(t_msh *msh, char *cmd);

/*
**  Function Declarations for builtin shell commands:
*/

int 	msh_cd(char **args);
int 	msh_exit(char **args);
int 	msh_pwd(char **args);

//TODO
int 	msh_echo(char **args);
int 	msh_export(char **args);
int 	msh_unset(char **args);
int 	msh_env(char **args);

int		builtin_caller(char **args);
int		is_builtin(char *cmd);
void	t_msh_init(t_msh *msh);

#endif