/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 20:38:02 by truby             #+#    #+#             */
/*   Updated: 2021/07/12 21:25:36 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

char	*ft_strjoin_shell(char *s1, char *s2)																		//надо подключить либу и удалить  эти статик функции
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new[i] = s1[i];
		i++;
	}
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s2);
	s2 = NULL;
	return (new);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

int		ft_error_int(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	return (0);
}

// void	*ft_error_null(char *str)
// {
// 	write(1, str, ft_strlen(str));
// 	write(1, "\n", 1);
// 	return (NULL);
// }