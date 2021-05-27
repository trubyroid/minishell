/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:37:00 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 00:59:47 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *stack, const char *ndl, size_t len)
{
	size_t			lenn;
	size_t			o;

	o = 0;
	lenn = ft_strlen(ndl);
	if ((stack == NULL && ndl == NULL) || ft_strlen(stack) < lenn || lenn > len)
		return (NULL);
	if (lenn == 0)
		return ((char *)stack);
	while (o <= len - lenn)
	{
		if (ft_strncmp(stack + o, ndl, lenn) == 0)
			return ((char *)stack + o);
		o++;
	}
	return (NULL);
}
