/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:33:27 by truby             #+#    #+#             */
/*   Updated: 2021/04/27 01:02:17 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*q;

	if (!lst)
		return ;
	q = *lst;
	while (q)
	{
		tmp = q->next;
		ft_lstdelone(q, del);
		q = tmp;
	}
	*lst = NULL;
}
