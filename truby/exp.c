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

void	print_export(t_env *env)
{
	t_env	*next;
	t_env	*first_lst;

	first_lst = create_new_lsts(env);							//какая-то дыра с переменными в нижнем регистре
	while (first_lst->str)
	{
		next = ft_find_next_lst(first_lst);
		write(1, next->str, ft_strlen(next->str));			//заменить strlen
		write(1, "\n", 1);
		first_lst = delete_previous_lst(next, first_lst);
		if (first_lst->next == NULL)
		{
			write(1, first_lst->str, ft_strlen(first_lst->str));
			write(1, "\n", 1);
			break ;
		}
	}
	free(first_lst);
}