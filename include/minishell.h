/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:43:58 by rlinkov           #+#    #+#             */
/*   Updated: 2021/06/29 15:47:15 by cduvivie         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "error.h"

/*
**	struct for keeping history of minishell
*/

typedef struct s_hist {
	int				fd;
	char			**history;
	unsigned int	cursor;
}					t_hist;

/*
**	struct for heredoc `<<`
*/

typedef struct s_heredoc {
	char		*eof_str;
	int			pipe_len;
	int			tmp_file_fd;
}				t_heredoc;

/*
**	struct for organizing data needed to execute commands
**	Description:
**	- command: holds core command ("cd", "echo", "pwd")
**	- option: option to cmd if any ("-n")
**	- arg: arguments of the cmd ("This is a string", "output.txt")
**	- in/out_file_fd: file descriptor of input/output
*/

typedef struct s_cmd_table {
	char			*cmd;
	char			*cmd_abs_path;
	int				argc;
	char			**argv;
	int				in_file_fd;
	int				out_file_fd;
	t_heredoc		*heredoc;
}					t_cmd_table;

/*
** Core struct which carries data of the minishell. 
*/

typedef struct s_msh {
	int				status;
	int				pid;
	int				heredoc;
	t_cmd_table		**t_cmds;
	int				t_cmds_len;
	char			**raw_cmds;
	int				raw_cmds_len;
	char			**env;
	t_hist			hist;
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
# define SPACE_TOK -10
# define DOUBLE_LCHEVRON -11
# define DOUBLE_RCHEVRON -12

# define MALLOC_FAILURE 1

# define NEW_COMMAND_PROMPT "(╯°□°)╯︵ ┻━┻$> "
# define HERE_DOC_PROMPT "> "
# define TMP_FILE_NAME "./.tmp_minishell_file.txt"
# define HISTORY_MSH "./.minishell_history"
# define HISTORY_MAX_SIZE 100

void	copy_env(char **envp);
void	prompt(void);
void	get_cmd(char **str);
void	handle_error(char *err_tag, int status);
char	*code_cmd(char *str);
char	*handle_dollar(int *i, char *full_cmd, int *sq);
char	*handle_pipe(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_lchevron(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_rchevron(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_space(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_backslash(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_quote(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_dquote(int *i, char *full_cmd, int *sq, int *dq);
char	*handle_semicolon(int *i, char *full_cmd, int *sq, int *dq);
char	*set_env_var(char *full_cmd, int *i);
void	syntaxe_cmd(char *full_cmd);
char	*remove_space(char *full_cmd);
char	*clean_cmd(char *str);
int		exec_cmd(t_cmd_table *t_cmd);
void	handle_signals(void);
void	add_space_for_chevron(char **cmd);

char	*find_var(char *var_name);
void	add_var_to_env(char *key, char *value);
void	set_env_value(char *key, char *value);
void	append_var_to_env(char *key, char *value);
int		is_key_existing(char *key);
int		is_key_valid(char *key, int size);
int		ft_isalpha_underscore(int c);
int		ft_isalnum_underscore(int c);
void	free_split(char **strs);
void	free_env(char **env);

/*
**  Function Declarations for builtin shell commands:
*/

int		msh_cd(t_cmd_table t_cmd);
void	msh_exit(t_cmd_table t_cmd);
int		msh_pwd(t_cmd_table t_cmd);
void	msh_echo(t_cmd_table t_cmd);
int		msh_export(t_cmd_table t_cmd);
void	msh_bi_export(t_cmd_table t_cmd);
int		msh_unset(t_cmd_table t_cmd);
void	msh_bi_unset(t_cmd_table t_cmd);
int		msh_env(t_cmd_table t_cmd);

/*
**  Builtin helper
*/

int		builtin_caller_in_parent(t_cmd_table *t_cmd);
void	builtin_caller_in_child(t_cmd_table *t_cmd);

int		is_our_builtin(char *cmd);

void	t_msh_init(void);
void	t_cmd_table_init(t_cmd_table *t_cmd);

/*
**	pipes/input/output management
*/

void	close_fd(t_cmd_table *t_cmd);
void	redirect_io(t_cmd_table *t_cmd);

void	exec_heredoc(t_cmd_table *t_cmd);
void	handle_heredoc(t_cmd_table *first_t_cmd, char *eof_str, int pipe_len);

void	check_redirections(t_cmd_table **t_cmds, int t_size);
void	handle_input_redirect(t_cmd_table *first_t_cmd, char *path);
void	handle_output_redirect(t_cmd_table *last_t_cmd, char *path, int mode);
void	set_pipes(t_cmd_table **t_cmds, int t_size);

/*
**	utility functions
*/

void	clean_empty_arg(t_cmd_table *t_cmd);
int		is_empty_str(const char *str);
void	exec_cmd_helper(int pid);
void	free_array_str(char **s, int len);
void	fill_t_cmd_argv(t_cmd_table	*t_cmd, char **tokens);

/*
**	fuctions for history functionality
*/

int		open_history_file(void);
void	add_command_to_history(const char *command);
void	create_hist_list(t_hist *hist);
void	write_history_file(int fd);
void	update_history_file(void);

/*
**	debug
*/

void	print_t_cmd_table(t_cmd_table *t_cmd);
void	print_list_t_cmd_table(t_cmd_table **t_cmd);

/*
**	free and exit
*/

void	free_t_cmd(t_cmd_table *t_cmd);
void	free_array_t_cmd(t_cmd_table **t_cmds, int len_t_cmds);
void	free_msh_and_exit(int exit_status);
void	free_array_str(char **s, int len);

#endif