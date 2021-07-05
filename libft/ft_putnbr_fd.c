/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 20:47:31 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:01:03 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int		g;

	if (n < 0)
	{
		write(fd, "-", 1);
		g = (-n);
	}
	else
		g = n;
	if (g >= 10)
		ft_putnbr_fd(g / 10, fd);
	ft_putchar_fd(g % 10 + 48, fd);
}
