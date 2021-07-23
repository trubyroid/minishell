/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 03:54:18 by truby             #+#    #+#             */
/*   Updated: 2021/07/24 01:37:29 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = -1;
	if (!str1 || !str2)
		return (-1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (-1);
	while (str1[++i] != '\0')
	{
		if (str1[i] != str2[i])
			return (-1);
	}
	return (0);
}
