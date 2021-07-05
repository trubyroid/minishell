/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:09:44 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:00:13 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		p;
	size_t		h;
	size_t		i;

	if (src == NULL && dst == NULL)
		return (0);
	if (ft_strlen(dst) > dstsize)
		return (dstsize + ft_strlen(src));
	h = ft_strlen(dst);
	p = ft_strlen(src) + h;
	dstsize -= h;
	i = 0;
	if (dstsize)
	{
		while (i < dstsize - 1 && src[i])
		{
			dst[h] = src[i];
			h++;
			i++;
		}
		dst[h] = '\0';
	}
	return (p);
}
