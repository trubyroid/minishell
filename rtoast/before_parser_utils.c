#include "../shell.h"

int	chek_symbol_dollar(char symbol)
{
	int	res;

	res = 0;
	if (symbol == '!' || symbol == '$' || symbol == '*')
		res = 1;
	if (symbol == '#' || symbol == '@' || symbol == '-')
		res = 1;
	return (res);
}

void	redirect_pars(t_all *tmp)
{
	int	i;

	i = 0;
	i = skipping_spaces(tmp, i);
	if (tmp->str[i] == '>' || tmp->str[i] == '<')
		tmp->redirect_i = redirect(tmp, i);
}

void	one_symbol(t_all *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'')
				i++;
		}
		if (tmp->str[i] == '\"')
		{
			i++;
			while (tmp->str[i] != '\"')
				i++;
		}
		if (tmp->str[i] == '&')
			error(258, "bash: syntax error near unexpected token `&'");
		if (tmp->str[i] == ')' && tmp->str[i + 1] == '(')
			error(258, "bash: syntax error near unexpected token `)'");
		i++;
	}
}

char	*func(char **str, char *original, char *replaced, int j)
{
	int		i;
	int		ri;
	int		len;
	int		rem_len;
	char	*new_str;

	len = (ft_strlen(*str)) - (ft_strlen(original)) + (ft_strlen(replaced));
	rem_len = len;
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	new_str[len] = '\0';
	i = -1;
	while (++i != j)
		new_str[i] = (*str)[i];
	len = i + ft_strlen(original);
	ri = -1;
	while (replaced[++ri] != '\0')
		new_str[i++] = replaced[ri];
	while ((*str)[len] != '\0' && i < rem_len)
	{
		new_str[i] = (*str)[len];
		i++;
		len++;
	}
	return (new_str);
}
