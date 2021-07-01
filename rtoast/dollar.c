#include "../shell.h"

void	search_dollar(t_all *tmp, t_env *lst)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (tmp->command_name)
		while (tmp->command_name[++i] != '\0')
			if (tmp->command_name[i] == '$')
				dollar_make(&(tmp->command_name), i, lst);
	i = -1;
	if (tmp->arg)
		while(tmp->arg[++i] != NULL)
		{
			while(tmp->arg[i][++j] != '\0')
			{
				if (tmp->arg[i][j] == '$')
				{
					dollar_make(&(tmp->arg[i]), j, lst);
				}
			}
			j = -1;
		}
}

void	dollar_make(char **str, int i, t_env *lst)
{
	char	*original;
	char	*replaced;

	original = NULL;
	replaced = NULL;
	original = find_original(*str, i);
	replaced = substitution(original, lst);
	create_new_str(str, original, replaced);
	if (original)
		free(original);
	if (replaced)
		free(replaced);
}

int		check_for_dollar(char symbol)
{
	int		res;

	res = 1;
	if (symbol == '_')
		res = 0;
	if (symbol >= 'a' && symbol <= 'z')
		res = 0;
	if (symbol >= 'A' && symbol <= 'Z')
		res = 0;
	if (symbol >= '0' && symbol <= '9')
		res = 0;
	return (res);
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
	while(check_for_dollar(str[++i]) == 0)
	{
		original[count] = str[i];
		count++;
	}
	return(original);
}

char	*substitution(char *original, t_env *lst)
{
	int	i;
	char	*replaced;

	i = ft_strlen(original);
	while (lst)
	{
		if(ft_strncmp(lst->str, original, i) == 0)
		{
			replaced = ft_strdup(&lst->str[i]);
			break ;
		}
		lst = lst->next;
	}
	return(replaced);
}

void	create_new_str(char **str, char *original, char *replaced)
{
	char	*new_str;
	int		len;
	int		rem_len;
	int		i;
	int		ri;

	i = -1;
	ri = -1;
	len = (ft_strlen(*str)) - (ft_strlen(original)) + (ft_strlen(replaced));
	rem_len = len;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	new_str[len] = '\0';
	while ((*str)[++i] != '$')
		new_str[i] = (*str)[i];
	len = i + ft_strlen(original);
	while (replaced[++ri] != '\0')
	{
		new_str[i] = replaced[ri];
		i++;
	}
	while ((*str)[len] != '\0' && i < rem_len)
	{
		new_str[i] = (*str)[len];
		i++;
		len++;
	}
	free(*str);
	*str = new_str;
}
