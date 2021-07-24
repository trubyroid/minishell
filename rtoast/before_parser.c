#include "../shell.h"

int	prepars(t_all *tmp)
{
	int	cod;

	init_tmp(tmp);
	cod = syntax_error(tmp);
	cod = cod - quotes_error(tmp);
	if (tmp->str != NULL)
	{
		one_symbol(tmp);
		redirect_pars(tmp);
		dollar_parser(tmp);
	}
	return (cod);
}

void	dollar_parser(t_all *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'' && tmp->str[i] != '\0')
				i++;
		}
		if (tmp->str[i] == '$')
		{
			if (chek_symbol_dollar(tmp->str[i + 1]) == 1)
				i = remove_dollar(tmp, i);
			if ((tmp->str[i + 1] >= '0' && tmp->str[i + 1] <= '9') \
					&& tmp->str[i + 2] == ' ')
				i = remove_dollar(tmp, i);
			if (tmp->str[i] != '$' && (check_for_dollar(tmp->str[i + 1]) != 0))
				i++;
		}
		if (tmp->str[i] == '$' && tmp->str[i + 1] == '$')
			i = remove_dollar(tmp, i);
		i++;
	}
}

int	syntax_error(t_all *tmp)
{
	int		i;
	char	q;

	i = -1;
	while (tmp->str[++i] != '\0')
	{
		if (tmp->str[i] == '\'' || tmp->str[i] == '\"')
		{
			q = tmp->str[i];
			i++;
			while (tmp->str[i] != q)
				i++;
		}
		if (error_cheker(tmp->str[i], tmp->str[i + 1], tmp->str[i + 2]) == 1)
			return (1);
	}
	if (i > 0 && tmp->str[i - 1] == '\\')
	{
		error(258, "bash: syntax error near unexpected token `\'");
		return (1);
	}
	return (0);
}

int	quotes_error(t_all *tmp)
{
	int		i;
	char	q;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'' || tmp->str[i] == '\"')
		{
			q = tmp->str[i];
			i++;
			while (tmp->str[i] != q && tmp->str[i] != '\0')
				i++;
			if (tmp->str[i] == '\0')
			{
				error(1, "bash: syntax error near unexpected token quotes");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	add_spase(int i, t_all *tmp)
{
	char	*temp;
	int		j;
	int		rem;

	j = ft_strlen(tmp->str) + 1;
	if (i != (j - 2))
	{
		temp = (char *)malloc(sizeof(char) * (j + 1));
		temp[j] = '\0';
		j = -1;
		while (++j < i)
			temp[j] = tmp->str[j];
		temp[j] = ' ';
		while (tmp->str[i] != '\0')
		{
			temp[++j] = tmp->str[i];
			i++;
		}
		free(tmp->str);
		tmp->str = temp;
	}
}
