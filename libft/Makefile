# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/23 09:41:00 by cduvivie          #+#    #+#              #
#    Updated: 2021/04/04 13:22:32 by cduvivie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I. -c

RM = /bin/rm -f

FILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_isspace.c \
	ft_strchr.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_calloc.c \
	ft_strlen.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_split_sep.c ft_strmapi.c \
	ft_atoi.c \
	ft_itoa.c ft_itoa_2.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putchar.c ft_putstr.c \
	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
	get_next_line.c get_next_line_utils.c \
	ft_abs.c \
	ft_check_file_extension.c \
	ft_stack.c \

OBJ	= $(FILES:%.c=%.o)

# Path to the different project folder
FT_PRINTF = ./ft_printf

all: $(NAME)

$(NAME): $(OBJ)
	@ ar rcs $(NAME) $(OBJ)
	$(MAKE) -C $(FT_PRINTF) all

$(OBJ): $(FILES)
	@ gcc $(CFLAGS) $(FILES)

clean:
	$(MAKE) -C $(FT_PRINTF) clean
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) -C $(FT_PRINTF) fclean
	@ echo "\033[32mFCLEAN DONE\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re
