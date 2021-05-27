/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 21:14:57 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:08:42 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*b;
	int		len;
	int		z;

	z = 0;
	len = ft_strlen(s);
	b = (char *)malloc(sizeof(char) * (len + 1));
	if (b == NULL)
		return (NULL);
	while (z < len)
	{
		b[z] = s[z];
		z++;
	}
	b[z] = '\0';
	return (b);
}
