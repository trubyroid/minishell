/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:27:31 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:01:42 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n != 0)
	{
		while (n)
		{
			if (*(unsigned char *)s == (unsigned char)c)
				return ((void *)s);
			s = s + 1;
			n--;
		}
	}
	return (0);
}
