/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:27:55 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 00:59:50 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	if (num == 0)
		return (0);
	while (num)
	{
		if ((*str1 != *str2) || ((*str1 == '\0') || (*str2 == '\0')))
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		str1++;
		str2++;
		num--;
	}
	return (0);
}
