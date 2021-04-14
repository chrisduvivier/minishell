/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:47:51 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/07 23:54:19 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../libft.h"

# define BUFF_SIZE 6

/*
**	struct `s_flags` allows the storage of flags used for the conversion.
*/

typedef struct s_flags
{
	int		left;
	int		zeropad;
	int		precision;
	int		min_w;
	int		max_w;
	int		plus;
	int		space;
	int		sharp;
	int		apostrophe;
	int		l;
	int		h;
}			t_flags;

/*
**	struct `s_printf_lst` contains all information needed that are not flags.
**	next points to the next node of the linked list.
*/

typedef struct s_printf_lst
{
	char				*str;
	char				percent;
	size_t				str_len;
	size_t				i;
	t_flags				flags;
	int					num_conv;
	int					zero;
	int					error;
	struct s_printf_lst	*next;
}						t_printf_lst;

/*
**	 ft_printf.c
*/

int				ft_printf(const char *format, ...);

/*
**	ft_itohex.c
*/

char			*ft_pf_append_hex_format(char *hex, char format);
char			*ft_itohex(uintmax_t nbr, char format);

/*
**	ft_printf_apply_flags.c
*/

t_printf_lst	*ft_pf_apply_thousand_sep(t_printf_lst *node);
t_printf_lst	*ft_pf_apply_flags(va_list *valist, t_printf_lst *node);

/*
**	ft_printf_conversion_1.c
*/

char			*ft_chartostr(int i);
t_printf_lst	*ft_pf_convert_c(t_printf_lst *node, uintmax_t c);
t_printf_lst	*ft_pf_convert_pc(t_printf_lst *node, int c);
t_printf_lst	*ft_pf_convert_s(t_printf_lst *node, const char *src);

/*
**	ft_printf_conversion_2.c
*/

t_printf_lst	*ft_pf_convert_d(t_printf_lst *node, long long int i);
t_printf_lst	*ft_pf_convert_u(t_printf_lst *node, unsigned long long int u);
t_printf_lst	*ft_pf_convert_p(t_printf_lst *node, uintmax_t num);
t_printf_lst	*ft_pf_convert_x(t_printf_lst *node, unsigned long long u,
					char form);

/*
**	ft_printf_format_bonus.c
*/

t_printf_lst	*ft_pf_read_argument_bonus(const char **format, va_list *valist,
					t_printf_lst *node);

/*
**	ft_printf_format.c
*/

t_printf_lst	*ft_pf_format_handler(const char **format, va_list *valist,
					t_printf_lst *node);
t_printf_lst	*ft_pf_read_argument(const char **format, va_list *valist,
					t_printf_lst *node);

/*
**	ft_printf_padding.c
*/

t_printf_lst	*ft_pf_apply_zero_pad(t_printf_lst *node, size_t pad_len,
					int sign);
t_printf_lst	*ft_pf_apply_space_pad(t_printf_lst *node, size_t pad_len);
t_printf_lst	*ft_pf_apply_min_w(t_printf_lst *node);

/*
**	ft_printf_precision.c
*/

t_printf_lst	*ft_pf_apply_precision(t_printf_lst *node);

/*
**	ft_printf_utils_1.c
*/

char			*ft_printf_strjoin(char const *s1, char const *s2,
					size_t len_s1, size_t len_s2);
size_t			count_digit(char *str);
char			ft_pf_check_sign(t_printf_lst *node);
int				ft_pf_is_zero(char *str);
t_printf_lst	*ft_pf_append_sign(t_printf_lst *node);

/*
**	ft_printf_utils_2.c
*/

int				ft_pf_atoi(const char **format);
int				append_zero_helper(t_printf_lst *node, char	**ptr, size_t i);
void			read_flags_helper(const char **format, t_printf_lst *node,
					va_list *valist);

/*
**	ft_resizing_str.c
*/

t_printf_lst	*ft_pf_resize(t_printf_lst *lst, size_t len);
t_printf_lst	*ft_pf_push(t_printf_lst *lst, char item);

/*
**	ft_t_printf_lst.c
*/

t_printf_lst	*ft_pf_t_lstnew(void);
void			ft_pf_t_lstdelone(t_printf_lst *lst);
t_printf_lst	*ft_pf_t_lstlast(t_printf_lst *lst);
void			ft_pf_t_lstadd_back(t_printf_lst **head, t_printf_lst *new);
void			ft_pf_t_lstclear(t_printf_lst **head);

#endif
