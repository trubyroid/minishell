#include "../shell.h"

void	bias(t_all *tmp, int i)
{
	while (tmp->arg[i] != NULL)
	{
		free(tmp->arg[i]);
		tmp->arg[i] = ft_strdup(tmp->arg[i + 1]);
		i++;
	}
}

int	chek_dollar_quotes(char *str, int i)
{
	int	doble_quotes;
	int	j;

	doble_quotes = 0;
	j = -1;
	while (++j != i)
	{
		if (str[j] == '\"')
			doble_quotes++;
	}
	if ((doble_quotes % 2) != 0)
		return (1);
	return (0);
}

int	check_for_dollar(char symbol)
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

void	command_dollar(t_all *tmp, t_env *lst)
{
	int	i;

	i = -1;
	while (tmp->command_name[++i] != '\0')
	{
		if (tmp->command_name[i] == '\'' && \
			chek_dollar_quotes(tmp->command_name, i) == 0)
		{
			i++;
			while (tmp->command_name[i] != '\'' && \
					tmp->command_name[i] != '\0')
				i++;
		}
		if (tmp->command_name[i] == '$' && \
			check_for_dollar(tmp->command_name[i + 1]) == 0)
			dollar_make(&(tmp->command_name), i, lst);
	}
}

void	arg_dollar(t_all *tmp, t_env *lst, int j)
{
	int	i;

	i = -1;
	while (tmp->arg[++i] != NULL)
	{
		while (tmp->arg[i][++j] != '\0')
		{
			if (tmp->arg[i][j] == '\'' && \
				chek_dollar_quotes(tmp->arg[i], j) == 0)
			{
				j++;
				while (tmp->arg[i][j] != '\'' && tmp->arg[i][j] != '\0')
					j++;
			}
			if (tmp->arg[i][j] == '$' && \
				check_for_dollar(tmp->arg[i][j + 1]) == 0)
			{
				if (dollar_make(&(tmp->arg[i]), j, lst) == 1)
					bias(tmp, i);
				j = -1;
			}
		}
		j = -1;
	}
}
