/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:26:28 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 00:51:00 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len_gnl(const char *str)
{
	int		i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i = i + 1;
	return (i);
}

int	ft_strchr_n(char *s)
{
	int		i;
	int		z;

	if (s == 0)
		return (0);
	i = 0;
	z = ft_len_gnl(s);
	while (i < z)
	{
		if (s[i] == 10)
			return (i + 1);
		i++;
	}
	return (0);
}

char	*ft_strdup_line(char *s)
{
	char	*b;
	int		len;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	b = (char *)malloc(sizeof(char) * (len + 1));
	if (b == NULL)
		return (NULL);
	len = 0;
	while (s[len] && s[len] != '\n')
	{
		b[len] = s[len];
		len++;
	}
	b[len] = '\0';
	return (b);
}

char	*ft_strdup_rem(char *s)
{
	char	*b;
	int		len;
	int		i;

	len = -1;
	i = 0;
	while (s[++len] != '\n')
	{
		if (s[len] == '\0')
		{
			free(s);
			return (0);
		}
	}
	b = (char *)malloc(sizeof(char) * (ft_len_gnl(s) - len + 1));
	if (b == NULL)
		return (NULL);
	while (s[++len])
		b[i++] = s[len];
	b[i] = '\0';
	free(s);
	return (b);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new = malloc(sizeof(char) * (ft_len_gnl(s1) + ft_len_gnl(s2) + 1));
	if (new == NULL)
		return (NULL);
	while (++i < ft_len_gnl(s1))
		new[i] = s1[i];
	while (i < ft_len_gnl(s1) + ft_len_gnl(s2))
		new[i++] = s2[++j];
	new[i] = '\0';
	if (s1)
		free(s1);
	return (new);
}
