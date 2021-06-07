/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:43:58 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/07 18:31:42 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "error.h"

/*
**	struct for organizing data needed to execute commands
**	Description:
**	- command: holds core command ("cd", "echo", "pwd")
**	- option: option to cmd if any ("-n")
**	- arg: arguments of the cmd ("This is a string", "output.txt")
**	- in_file_fd: file descriptor of input (STD_IN as default)
**	- out_file_fd: file descriptor of output. This could be a new file (STD_OUT as default)
**	- next: pointer to next cmd
*/
typedef struct s_cmd_table {
	char 				*cmd;
	char				*cmd_abs_path;
	int					argc;
	char 				**argv;
	int 				in_file_fd;
	int 				out_file_fd;
	struct s_cmd_table	*next;
}						t_cmd_table;

/*
** Core struct which carries data of the minishell. 
*/
typedef struct s_msh {
	int				status;
	int				pid;
	t_cmd_table		*cmd_t;
	char			**env;
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

# define MALLOC_FAILURE 1

# define NEW_COMMAND_PROMPT "(╯°□°)╯︵ ┻━┻$> "

void	copy_env(char **envp);
void	prompt(void);
void    get_cmd(char **str);
void	handle_error(char *err_tag);
char	*code_cmd(char *str);
char	*set_env_var(char *full_cmd, int *i);
int		syntaxe_cmd(char *full_cmd);
char    *remove_space(char *full_cmd);
char    *clean_cmd(char *str);
int		exec_cmd(t_cmd_table t_cmd);

char	*find_var(char *var_name);
void	set_env_value(char *key, char *value);


/*
**  Function Declarations for builtin shell commands:
*/

int 	msh_cd(t_cmd_table cmd_t);
int 	msh_exit(t_cmd_table cmd_t);
int 	msh_pwd(t_cmd_table cmd_t);
void 	msh_echo(t_cmd_table cmd_t);
int 	msh_export(t_cmd_table cmd_t);
void	msh_bi_export(t_cmd_table cmt_t);
int 	msh_unset(t_cmd_table cmd_t);
int 	msh_env(t_cmd_table cmd_t);

/*
**  Builtin helper
*/

int		builtin_caller_in_parent(t_cmd_table t_cmd);
void	builtin_caller_in_child(t_cmd_table t_cmd);

int		is_our_builtin(char *cmd);

void	t_msh_init(void);
void	t_cmd_table_init(t_cmd_table *cmd_t);


/*
**	input/output management
*/
void    check_redirections(t_cmd_table *t_cmds, int t_size);
void	handle_input_redirection(t_cmd_table *first_t_cmd, char *path);
void	handle_output_redirection(t_cmd_table *last_t_cmd, char *path, int mode);
void	set_pipes(t_cmd_table *t_cmds, int t_size);

/*
**	debug
*/

void	print_t_cmd_table(t_cmd_table t_cmd);

/*
**	free and exit
*/

void    free_t_cmd(t_cmd_table *t_cmd);


#endif