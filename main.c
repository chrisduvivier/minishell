/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 19:22:29 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/19 18:20:29 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

/*
**  Function Declarations for builtin shell commands:
*/

int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

/*
**  List of builtin commands, followed by their corresponding functions.
*/

char *builtin_str[] = {
	"cd",
	"help",
	"exit"};

int (*builtin_func[])(char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit};

int lsh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int lsh_cd(char **args)
{
	// ft_printf("CDDDDDDDDDDDDD\n");
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}
	return 1;
}

int lsh_help(char **args)
{
	int i;
	printf("Stephen Brennan's LSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < lsh_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs.\n");
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
}

int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		if (execvp(args[0], args) == -1)
		{
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		// Error forking
		perror("lsh");
	}
	else
	{
		// Parent process
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_execute(char **args)
{
	int i;

	if (args[0] == NULL)
	{
		// An empty command was entered.
		return 1;
	}

	for (i = 0; i < lsh_num_builtins(); i++)
	{
		if (ft_strcmp(args[0], builtin_str[i]) == 0)
		{
			return (*builtin_func[i])(args);
		}
	}

	return lsh_launch(args);
}

/*
**  Following tutorial
*/

void lsh_loop(void)
{
	char *line;
	char **args;
	int status;
	int ret;

	status = 1; //set default
	while (status)
	{
		ft_printf("> ");
		ret = get_next_line(STDIN_FILENO, &line); // we need only 1 line
		args = ft_split(line, ' ');				  // only considers whilespace ' ' as seperator
		status = lsh_execute(args);				  // execute the given commands

		free(line);
		free(args);
	}
}

int main(int argc, char **argv)
{
	// Load config files, if any.

	// Run command loop.
	lsh_loop();

	// Perform any shutdown/cleanup.

	return EXIT_SUCCESS;
}