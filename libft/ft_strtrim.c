/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:16:16 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 00:59:36 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	begin(char const *s1, char const *set)
{
	size_t				o;
	size_t				i;

	o = 0;
	i = 0;
	while (set[o] != '\0' && i != ft_strlen(s1))
	{
		if (s1[i] != set[o])
			o++;
		else
		{
			i++;
			o = 0;
		}
	}
	return (i);
}

static size_t	end(const char *s1, const char *set, size_t i)
{
	size_t				o;

	o = 0;
	while (set[o] != '\0' && i > 0)
	{
		if (s1[i] != set[o])
			o++;
		else
		{
			i--;
			o = 0;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char				*n;
	size_t				g;
	size_t				i;
	size_t				h;

	h = 0;
	if (s1 == 0 || set == 0)
		return (NULL);
	g = begin(s1, set);
	if (g == ft_strlen(s1))
		return (ft_strdup(""));
	i = end(s1, set, ft_strlen(s1) - 1);
	n = (char *)malloc(sizeof(char) * (i - g + 2));
	if (n == NULL)
		return (NULL);
	while (g <= i)
	{
		n[h] = s1[g];
		h++;
		g++;
	}
	n[h] = '\0';
	return (n);
}
