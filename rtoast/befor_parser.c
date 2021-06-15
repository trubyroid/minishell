#include "../shell.h"

void	error(int i)
{
	i = 4;
	printf("Error");
	exit(1);
}

void	prepars(t_all *tmp)
{
	int i;
	int two_e;
	int one_e;

	i = 0;
	two_e = 0;
	one_e = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '"' && quotes_in_quotes(tmp, i) == 0)
			two_e++;
		if (tmp->str[i] == '\'' && quotes_in_quotes(tmp, i) == 0)
			one_e++;
		if (tmp->str[i] == ';' && tmp->str[i + 1] == ';')
			error(1);
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '<' && tmp->str[i + 2] == '<')
			error(1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '>' && tmp->str[i + 2] == '>')
			error(1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '<')
			error(1);
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '>')
			error(1);
		i++;
	}
	if (two_e < 0)
		two_e = 0;
	if (one_e < 0)
		one_e = 0;
	if (two_e % 2 != 0 && two_e > 0)
		error(1);
	if (one_e % 2 != 0 && one_e > 0)
		error(1);
	if (tmp->str[i - 1] == '\\')
		error(1);
}

int		quotes_in_quotes(t_all *tmp, int i)
{
	if (tmp->str[i - 1] == '\'' && tmp->str[i + 1] == '\'')
		return (1);
	if (tmp->str[i - 1] == '"' && tmp->str[i + 1] == '"')
		return (1);
	return (0);
}
