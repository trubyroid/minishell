/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 01:55:47 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:03:09 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*h;
	size_t			i;

	i = 0;
	h = (void *)malloc(sizeof(char) * (num * size));
	if (h == NULL)
		return (NULL);
	while (i < num * size)
	{
		h[i] = '0';
		i++;
	}
	return (h);
}
