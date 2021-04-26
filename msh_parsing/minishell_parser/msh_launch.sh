(cd ../libft/ && make)
gcc -Wall -Werror -Wextra minishell.c clean_cmd.c syntaxe_cmd.c error.c ft_split_msh.c ../libft/libft.a
(cd ../libft/ && make fclean)
clear
echo "Prompt loop : CTRL+D OR CTRL+C to quit\n"
./a.out
