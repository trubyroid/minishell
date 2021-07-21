#include "../shell.h"

void	search_dollar(t_all *tmp, t_env *lst)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (tmp->command_name)
		while (tmp->command_name[++i] != '\0')
		{
			if (tmp->command_name[i] == '\'' && chek_dollar_quotes(tmp->command_name, i) == 0)
			{
				i++;
				while (tmp->command_name[i] != '\'' && tmp->command_name[i] != '\0')
					i++;
			}
			if (tmp->command_name[i] == '$' && check_for_dollar(tmp->command_name[i + 1]) == 0)
				dollar_make(&(tmp->command_name), i, lst);
		}
	i = -1;
	if (tmp->arg)
		while(tmp->arg[++i] != NULL)
		{
			while(tmp->arg[i][++j] != '\0')
			{
				if (tmp->arg[i][j] == '\'' && chek_dollar_quotes(tmp->arg[i], j) == 0)
				{
					j++;
					while (tmp->arg[i][j] != '\'' && tmp->arg[i][j] != '\0')
						j++;
				}
				if (tmp->arg[i][j] == '$' && check_for_dollar(tmp->arg[i][j + 1]) == 0)
				{
					if (dollar_make(&(tmp->arg[i]), j, lst) == 1)
						bias(tmp, i);
					j = -1;
				}
			}
			j = -1;
		}
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

int		check_for_dollar(char symbol)
{
	int		res;

	res = 1;
	if (symbol == '_')
		res = 0;
	if (symbol == '?')
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
	replaced = NULL;
	while (lst)
	{
		if(ft_strncmp(lst->str, original, i) == 0)
		{
			replaced = ft_strdup(&lst->str[i]);
			break ;
		}
		lst = lst->next;
	}
	if (original[0] == '?')
		replaced = ft_itoa(g_status);
	g_status = 0;
	return(replaced);
}

void	create_new_str(char **str, char *original, char *replaced, int j)
{
	char	*new_str;
	int		len;
	int		rem_len;
	int		i;
	int		ri;

	i = -1;
	ri = -1;
	len = (ft_strlen(*str)) - (ft_strlen(original)) + (ft_strlen(replaced));
	if (len == 0)
		new_str = ft_strdup("\0");
	else
	{
		rem_len = len;
		new_str = (char *)malloc(sizeof(char) * (len + 1));
		new_str[len] = '\0';
		while (++i != j)
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
	}
	free(*str);
	*str = new_str;
}

void	bias(t_all *tmp, int i)
{
	while (tmp->arg[i] != NULL)
	{
		free(tmp->arg[i]);
		tmp->arg[i] = ft_strdup(tmp->arg[i + 1]);
		i++;
	}
}

int		chek_dollar_quotes(char *str, int i)
{
	int	doble_quotes;
	int j;

	doble_quotes = 0;
	j = -1;
	while (++j != i)
	{
		if (str[j] == '\"')
			doble_quotes++;
	}
	if ((doble_quotes % 2) != 0)
		return (1);
	return(0);
}
