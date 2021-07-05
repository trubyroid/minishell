/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 19:36:47 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:00:26 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;
	int	z;

	if (s == NULL)
		return (NULL);
	i = 0;
	z = ft_strlen(s);
	while (i <= z)
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (0);
}
