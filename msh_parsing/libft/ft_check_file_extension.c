/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file_extension.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduvivie <cduvivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:00:48 by cduvivie          #+#    #+#             */
/*   Updated: 2021/04/02 20:19:14 by cduvivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  Verify if filename ends with the given format (extension)
**  @param filename: filename (ex: "texture_1.cub")
**  @param format: extension starting with comman (ex: ".cub")
*/

int	ft_check_file_extension(char *filename, char *format)
{
	int	i;
	int	len1;
	int	len2;

	len1 = ft_strlen(filename);
	len2 = ft_strlen(format);
	i = 1;
	while (filename[len1 - i] && len2 - i >= 0)
	{
		if (filename[len1 - i] != format[len2 - i])
			return (0);
		i++;
	}
	return (1);
}
