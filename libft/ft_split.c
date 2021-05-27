/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 21:53:42 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:08:04 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	qword(char const *s, char c)
{
	size_t				i;
	size_t				g;

	i = 0;
	g = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			g++;
		i++;
	}
	return (g);
}

static unsigned int	find(char const *s, char c)
{
	unsigned int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if (s[i] != c)
			return (i);
	}
	return (i);
}

static size_t	qchar(char const *s, char c, unsigned int g)
{
	size_t				i;

	i = 0;
	while (s[g] != c && s[g] != '\0')
	{
		i++;
		g++;
	}
	return (i);
}

static void	*ft_free(char **sp, unsigned int o)
{
	unsigned int		f;

	f = 0;
	while (f <= o)
	{
		free(sp[f]);
		f++;
	}
	free(sp);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int					w;
	size_t				ch;
	char				**sp;
	unsigned int		g;
	int					o;

	if (s == NULL)
		return (NULL);
	o = 0;
	w = qword(s, c);
	sp = (char **)malloc(sizeof(char *) * (w + 1));
	if (sp == NULL)
		return (NULL);
	while (o != w)
	{
		g = find(s, c);
		ch = qchar(s, c, g);
		sp[o] = ft_substr(s, g, ch);
		if (sp[o] == NULL)
			return (ft_free(sp, o));
		o++;
		s = s + g + ch;
	}
	sp[o] = NULL;
	return (sp);
}
