/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 00:44:51 by truby             #+#    #+#             */
/*   Updated: 2021/07/26 18:57:15 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

void	ft_error(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

void	ft_error_exit(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(i);
}

int	ft_error_int(char *str, int i, int fl)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	if (fl == 1)
		exit(i);
	return (0);
}

void	*ft_error_null(char *str, int i)
{
	g_status = i;
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (NULL);
}
