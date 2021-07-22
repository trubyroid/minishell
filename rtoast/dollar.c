#include "../shell.h"

void	search_dollar(t_all *tmp, t_env *lst)
{
	int	j;

	j = -1;
	if (tmp->command_name)
		command_dollar(tmp, lst);
	if (tmp->arg)
		arg_dollar(tmp, lst, j);
}

int	dollar_make(char **str, int i, t_env *lst)
{
	char	*original;
	char	*replaced;
	int		determinant;

	determinant = 0;
	original = find_original(*str, i);
	replaced = substitution(original, lst);
	if (replaced == NULL)
	{
		determinant = 2;
		replaced = ft_strdup("");
	}
	create_new_str(str, original, replaced, i);
	if (determinant == 2 && *str[0] == '\0')
		determinant = 1;
	if (original)
		free(original);
	if (replaced)
		free(replaced);
	return (determinant);
}

char	*find_original(char *str, int i)
{
	char	*original;
	int		count;

	count = 0;
	while (check_for_dollar(str[++i]) == 0)
		count++;
	original = (char *)malloc(sizeof(char) * count + 2);
	original[count] = '=';
	original[count + 1] = '\0';
	i = i - count - 1;
	count = 0;
	while (check_for_dollar(str[++i]) == 0)
	{
		original[count] = str[i];
		count++;
	}
	return (original);
}

char	*substitution(char *original, t_env *lst)
{
	int		i;
	char	*replaced;

	i = ft_strlen(original);
	replaced = NULL;
	while (lst)
	{
		if (ft_strncmp(lst->str, original, i) == 0)
		{
			replaced = ft_strdup(&lst->str[i]);
			break ;
		}
		lst = lst->next;
	}
	if (original[0] == '?')
		replaced = ft_itoa(g_status);
	g_status = 0;
	return (replaced);
}

void	create_new_str(char **str, char *original, char *replaced, int j)
{
	char	*new_str;
	int		len;

	len = (ft_strlen(*str)) - (ft_strlen(original)) + (ft_strlen(replaced));
	if (len == 0)
		new_str = ft_strdup("\0");
	else
		new_str = func(str, original, replaced, j);
	free(*str);
	*str = new_str;
}
