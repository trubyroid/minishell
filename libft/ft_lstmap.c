/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:37:23 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:07:05 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *))
{
	t_list	*q;
	t_list	*s;
	t_list	*iter;

	iter = l;
	if (!l)
		return (NULL);
	q = ft_lstnew(f(l->content));
	if (q == NULL)
		return (NULL);
	s = q;
	while (iter->next)
	{
		iter = iter->next;
		s->next = ft_lstnew(f(iter->content));
		if (s->next == NULL)
		{
			ft_lstclear(&q, d);
			return (NULL);
		}
		s = s->next;
	}
	return (q);
}
