/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:46:55 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:04:35 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_calloc_char(int num, char a)
{
	char				*h;
	int					i;

	i = -1;
	h = (char *)malloc(sizeof(char) * num + 1);
	if (h == NULL)
		return (NULL);
	while (++i < num)
		h[i] = a;
	h[i] = '\0';
	return (h);
}
