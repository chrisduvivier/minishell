# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/07 21:00:40 by cduvivie          #+#    #+#              #
#    Updated: 2021/04/19 20:52:51 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC 			:=	gcc
# CFLAGS	 	:=	-Wall -Wextra -Werror
RM 			:=	/bin/rm -f

LIBFT		:= libft/libft.a

# C filenames of the project
SRCS 		:= 	main.c

OBJ			:=	$(SRCS:%.c=%.o)

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(LIBFT)
	@ $(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
	@ $(MAKE) -C ./libft

clean		:
	@ $(RM) $(OBJ)
	@ $(MAKE) -C ./libft clean

fclean		:	clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C ./libft fclean

re			: fclean all

.PHONY		: all clean fclean re