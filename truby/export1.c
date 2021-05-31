#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct 	s_env
{
	char				*str;
	struct s_env		*next;
}				t_env;

// static t_env	**ft_sort(t_env **lst, int qua_str)
// {
// 	int i = -1;
// 	int j = -1;
// 	t_env *extra;

// 	while (++i < qua_str)
// 	{
// 		while (++j < qua_str - 1)
// 		{
// 			if (strcmp(lst[j]->str, lst[j + 1]->str) > 0)						//заменить на свою функцию
// 			{
// 				extra = lst[j];
// 				lst[j] = lst[j + 1];
// 				lst[j + 1] = extra;
// 			}
// 		}
// 		j = -1;
// 	}
// 	return (lst);
// }

static char	*ft_sort_list(t_env *lst, int qua_str)
{
	int k;
	t_env *extra;
	t_env *first;

	extra = lst->next;
	first = lst;
	while (extra->next != NULL)
	{
		k = strcmp(first->str, extra->str);			//заменить на свою функцию
		if (k <= 0)
			extra = extra->next;
		else
		{
			// lst->next = extra->next;
			// extra->next = lst;
			first = extra;
			extra = extra->next;
		}
	}
	write(1, first->str, strlen(first->str));			//заменить strlen
	write(1, "\n", 1);
	while (lst->next != NULL)
	{
		if (lst->next == first)
		{
			extra = lst->next;
			lst->next = extra->next;
			extra->next = NULL;
			free(extra);
		}
		lst = lst->next;
	}
	return (NULL);
}

// int	main(int ac, char **av, char **env)
// {
// 	int i = 0;
// 	int j = 0;
// 	t_env	**envi;
// 	t_env	*lst = NULL;
// 	t_env	*new = NULL;

// 	while (env[i + 1] != NULL)
// 		i++;
// 	j = i;
// 	if (!(envi = malloc(sizeof(t_env) * j)))
// 		return (0);
// 	if (!(lst = malloc(sizeof(t_env *))))
// 		return (0);
// 	lst->str = env[i];
// 	lst->next = NULL;
// 	envi[i] = lst;
// 	while (--i >= 0)
// 	{
// 		if (!(new = malloc(sizeof(t_env *))))
// 			return (0);
// 		new->str = env[i];
// 		new->next = lst;
// 		lst = new;
// 		envi[i] = lst;
// 	}
// 	envi = ft_sort(envi, j);
// 	printf("%s\n", envi[0]->next->str);
// 	return (0);

// }

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
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	ft_sort_list(lst, j);
	write(1,"nn", 2);
	write(1, lst->next->str, strlen(lst->next->str));
	// write(1, s, strlen(s));
	// write(1, "\n", 1);
	// s = ft_sort_list(lst->next, j - 1);
	// write(1, s, strlen(s));
	// printf("%s", lst->str);
	// printf("%s", lst->str);
	return (0);

}