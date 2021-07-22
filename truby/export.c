/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 01:43:38 by truby             #+#    #+#             */
/*   Updated: 2021/07/23 02:02:21 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static t_env	*ft_find_next_lst(t_env *lst)
{
	int		k;
	t_env	*extra;
	t_env	*first;

	extra = lst->next;
	first = lst;
	while (extra != NULL)
	{
		k = ft_strncmp(first->str, extra->str, ft_strlen(first->str));
		if (k <= 0)
			extra = extra->next;
		else
		{
			first = extra;
			extra = extra->next;
		}
	}
	return (first);
}

static t_env	*delete_previous_lst(t_env *lst, t_env *first, t_env *extra)
{
	if (lst == first)
	{
		first = first->next;
		lst->next = NULL;
		free(lst);
		lst = NULL;
	}
	else
	{
		while (extra != NULL)
		{
			if (extra->next == lst)
			{
				extra->next = lst->next;
				lst->next = NULL;
				free(lst);
				lst = NULL;
				break ;
			}
			extra = extra->next;
		}
	}
	return (first);
}

static t_env	*print_last_variable(t_env *last)
{
	char	*value;
	int		j;

	j = 0;
	while (last->str[j] != '=' && last->str[j])
		j++;
	j++;
	write(1, "declare -x ", 11);
	write(1, last->str, j);
	if (ft_strchr(last->str, '='))
	{
		value = ft_substr_shell(last->str, j, ft_strlen(last->str) - j + 1);
		if (!value)
			return (ft_error_null("Error of malloc.", ENOMEM));
		write(1, value, ft_strlen(value));
		free(value);
		value = NULL;
	}
	write(1, "\n", 1);
	free(last);
	last = NULL;
	return (last);
}

static t_env	*print_variables(t_env *first_lst)
{
	int		j;
	t_env	*next;
	char	*value;

	j = 0;
	next = ft_find_next_lst(first_lst);
	while (next->str[j] != '=' && next->str[j])
		j++;
	j++;
	write(1, "declare -x ", 11);
	write(1, next->str, j);
	if (ft_strchr(next->str, '='))
	{
		value = ft_substr_shell(next->str, j, ft_strlen(next->str) - j + 1);
		if (!value)
			return (ft_error_null("Error of malloc.", ENOMEM));
		write(1, value, ft_strlen(value));
		free(value);
		value = NULL;
	}
	write(1, "\n", 1);
	return (next);
}

void	print_export(t_env *env)
{
	t_env	*first_lst;
	t_env	*previous;
	int		j;
	char	*value;

	first_lst = copy_lst(env);
	while (first_lst != NULL)
	{
		previous = print_variables(first_lst);
		first_lst = delete_previous_lst(previous, first_lst, first_lst);
		if (first_lst->next == NULL)
			first_lst = print_last_variable(first_lst);
	}
	g_status = 0;
}
