/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 02:18:04 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:02:42 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*array(char *k, unsigned int o, int g)
{
	while (o > 0 || g >= 0)
	{
		k[g] = o % 10 + '0';
		o = o / 10;
		g--;
	}
	return (k);
}

static int	qchar(unsigned int o, int g)
{
	while (o >= 10)
	{
		o = o / 10;
		g += 1;
	}
	return (g);
}

char	*ft_itoa(int n)
{
	char			*k;
	unsigned int	o;
	int				g;
	int				u;

	g = 1;
	u = 0;
	o = n;
	if (n < 0)
	{
		o = (-n);
		g++;
		u++;
	}
	g = qchar(o, g);
	k = (char *)malloc(sizeof(char) * (g + 1));
	if (k == NULL)
		return (NULL);
	k[g--] = '\0';
	k = array(k, o, g);
	if (u == 1)
		k[0] = '-';
	return (k);
}
