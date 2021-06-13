#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct 	s_env
{
	char				*str;
	struct s_env		*next;
}				t_env;

// static char	*ft_sort_list(t_env *lst, int qua_str)
// {
// 	int k;
// 	t_env *extra;
// 	t_env *first;

// 	extra = lst->next;
// 	first = lst;
// 	while (extra->next != NULL)
// 	{
// 		k = strcmp(first->str, extra->str);			//заменить на свою функцию
// 		if (k <= 0)
// 			extra = extra->next;
// 		else
// 		{
// 			// lst->next = extra->next;
// 			// extra->next = lst;
// 			first = extra;
// 			extra = extra->next;
// 		}
// 	}
// 	write(1, first->str, strlen(first->str));			//заменить strlen
// 	write(1, "\n", 1);
// 	while (lst->next != NULL)
// 	{
// 		if (lst->next == first)
// 		{
// 			extra = lst->next;
// 			lst->next = extra->next;
// 			extra->next = NULL;
// 			free(extra);
// 		}
// 		lst = lst->next;
// 	}
// 	return (NULL);
// }


static t_env    *ft_sort_list(t_env *lst)
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
	write(1, first->str, strlen(first->str));			//заменить strlen
	write(1, "\n", 1);
    if (lst == first)
    {
        first_one = lst->next;
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
	return (first_one);
}

int	main(int ac, char **av, char **env)
{
	int i = 0;
	int j = 0;
	t_env	*lst = NULL;
	t_env	*new = NULL;
	char	*s;

	while (env[i + 1] != NULL)
		i++;
	j = i;
	if (!(lst = malloc(sizeof(t_env *))))
		return (0);
	lst->str = env[i];
	lst->next = NULL;
	while (--i >= 0)
	{
		if (!(new = malloc(sizeof(t_env *))))
			return (0);
		new->str = env[i];
		new->next = lst;
		lst = new;
	}
	while (lst->next != NULL)
		lst = ft_sort_list(lst);
	return (0);

}