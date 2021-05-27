/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:22:12 by truby             #+#    #+#             */
/*   Updated: 2021/04/28 19:32:09 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tenthou(char *line, int *i, int *rgb)
{
	while (ft_isdigit(line[*i]))
	{
		*rgb = (*rgb) * 10 + (line[(*i)++] - '0');
		if (*rgb > 10000)
			return (-1);
	}
	if (rgb <= 0)
		return (-1);
	return (1);
}
