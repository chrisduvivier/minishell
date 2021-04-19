# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/26 15:07:06 by cduvivie          #+#    #+#              #
#    Updated: 2020/02/24 10:53:23 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
CC = gcc
CFLAGS = -I. -c
OPTIONS = -Wall -Wextra -Werror
RM = /bin/rm -f

FILES = ft_printf.c \
	ft_printf_format.c \
	ft_itohex.c \
	ft_resizing_str.c \
	ft_t_printf_lst.c \
	ft_printf_apply_flags.c \
	ft_printf_precision.c \
	ft_printf_padding.c \
	ft_printf_utils_1.c \
	ft_printf_utils_2.c \
	ft_printf_conversion_1.c \
	ft_printf_conversion_2.c \
	ft_printf_format_bonus.c \
	
OBJ	= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ cp ../libft.a $(NAME)
	@ ar rcs $(NAME) $(OBJ)
	@ mv $(NAME) ../libft.a

$(OBJ): $(FILES)
	@ $(CC) $(CFLAGS) $(FILES)

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re