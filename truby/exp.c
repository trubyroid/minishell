#include "shell_truby.h"

static t_env    *ft_find_next_lst(t_env *lst)
{
	int k;
	t_env *extra;
	t_env *first;
    t_env *first_one;

	extra = lst->next;
	first = lst;
	first_one = lst;
	while (extra->next != NULL)
	{
		k = strcmp(first->str, extra->str);			//заменить на свою функцию
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

static t_env	*delete_previous_lst(t_env *lst, t_env *first)
{
	t_env	*extra;

    if (lst == first)
    {
        first = lst->next;
        lst->next = NULL;
        free(lst);
    }
    else
    {
	    while (lst->next != NULL)
	    {
	    	if (lst->next == first)
	    	{
	    		extra = lst->next;
	    		lst->next = extra->next;
	    		extra->next = NULL;
	    		free(extra);
                break;
	    	}
	    	lst = lst->next;
	    }
    }
	return (first);
}

static t_env	*create_new_lsts(t_env *env)
{
	// int i;
	// int j;
	// t_env	*lst;
	// t_env	*new;
	// char	*s;

	// i = 0;
	// j = 0;
	// lst = NULL;
	// new = NULL;
	// while (env[i + 1] != NULL)
	// 	i++;
	// j = i;
	// lst = malloc(sizeof(t_env *));					//send it to begin of programm
	// if (!lst)
	// 	return (0);
	// lst->str = env[i];
	// lst->next = NULL;
	// while (--i >= 0)
	// {
	// 	new = malloc(sizeof(t_env *));
	// 	if (!new)
	// 		return (0);
	// 	new->str = env[i];
	// 	new->next = lst;
	// 	lst = new;
	// }
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

void	print_export(t_env *env)
{
	t_env	*next;
	t_env	*first_lst;

	first_lst = create_new_lsts(env);
	while (first_lst->next != NULL)
	{
		next = ft_find_next_lst(first_lst);
		write(1, next->str, strlen(next->str));			//заменить strlen
		write(1, "\n", 1);
		first_lst = delete_previous_lst(next, first_lst);
	}
}