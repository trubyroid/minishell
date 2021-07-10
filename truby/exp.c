/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truby <truby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 20:30:05 by truby             #+#    #+#             */
/*   Updated: 2021/07/10 20:49:30 by truby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_truby.h"

static char		*ft_substr_shell(char const *s, unsigned int start, size_t len)
{
	char		*b;
	size_t		z;

	z = 1;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	b = (char *)malloc(sizeof(char) * (len + 3));
	if (b == NULL)
		return (NULL);
	b[0] = '"';
	while (z < len)
	{
		b[z] = s[start];
		z++;
		start++;
	}
	b[z] = '"';
	b[++z] = '\0';
	return (b);
}

static t_env    *ft_find_next_lst(t_env *lst)
{
	int k;
	t_env *extra;
	t_env *first;
    t_env *first_one;

	extra = lst->next;
	first = lst;
	first_one = lst;
	while (extra->str)
	{
		k = strcmp(first->str, extra->str);			//заменить на свою функцию
		if (k <= 0)
			extra = extra->next;
		else
		{
			first = extra;
			extra = extra->next;
		}
		if (extra == NULL)
			break ;
	}
	return (first);
}

static t_env	*delete_previous_lst(t_env *lst, t_env *first)
{
	t_env	*extra;

	extra = first;
    if (lst == first)
    {
        first = lst->next;
        lst->next = NULL;
        free(lst);
		lst = NULL;
    }
    else
    {
		while (extra->str)
	    {
	    	if (extra->next == lst)
	    	{
	    		extra->next = lst->next;
	    		lst->next = NULL;
	    		free(lst);
				lst = NULL;
                break;
	    	}
	    	extra = extra->next;
			if (extra == NULL)
				break ;
	    }
    }
	return (first);
}

static t_env	*create_new_lsts(t_env *env)
{
	t_env	*new;
	t_env	*extra;
	t_env	*first;
	int i;
	int j;

	new = malloc(sizeof(t_env *));
	if (!new)
		return (0);
	first = new;
	new->str = env->str;
	env = env->next;
	while (env->next != NULL)
	{
		extra = malloc(sizeof(t_env *));
		if (!extra)
			return (0);
		new->next = extra;
		extra->str = env->str;
		new = extra;
		env = env->next;
	}
	extra = malloc(sizeof(t_env *));
	if (!extra)
		return (0);
	new->next = extra;
	extra->str = env->str;
	extra->next = NULL;
	return (first);
}

void	print_export(t_env *env)						//поработать над export с долларом
{
	t_env	*next;
	t_env	*first_lst;
	int		j;
	char	*value;

	j = 0;
	first_lst = create_new_lsts(env);
	while (first_lst->str)
	{
		next = ft_find_next_lst(first_lst);
		while (next->str[j] != '=' && next->str[j])
			j++;
		j++;
		write(1, "declare -x ", 11);
		write(1, next->str, j);
		if (ft_strchr(next->str, '='))
		{
			value = ft_substr_shell(next->str, j, ft_strlen(next->str) - j + 1);
			write(1, value, ft_strlen(value));
			free(value);
			value = NULL;
		}
		write(1, "\n", 1);
		j = 0;
		first_lst = delete_previous_lst(next, first_lst);
		if (first_lst->next == NULL)
		{
			while (first_lst->str[j] != '=' && first_lst->str[j])
				j++;
			j++;
			write(1, "declare -x ", 11);
			write(1, first_lst->str, j);
			if (ft_strchr(first_lst->str, '='))
			{
				value = ft_substr_shell(first_lst->str, j, ft_strlen(first_lst->str) - j + 1);
				write(1, value, ft_strlen(value));
				free(value);
				value = NULL;
			}
			write(1, "\n", 1);
			break ;
		}
	}
	free(first_lst);
	first_lst = NULL;
}