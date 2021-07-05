/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 20:16:16 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 00:59:55 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*h;
	unsigned int	i;
	size_t			r;

	if (s == NULL)
		return (NULL);
	i = 0;
	r = ft_strlen(s);
	h = (char *)malloc(sizeof(char) * (r + 1));
	if (h == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		h[i] = f(i, s[i]);
		i++;
	}
	h[i] = '\0';
	return (h);
}
