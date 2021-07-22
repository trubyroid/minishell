#include "../shell.h"

void	remove_quotes(t_all *tmp, int i)
{
	int	s;
	int	quotes;

	s = 0;
	while (tmp->arg[i][s] != '\0')
	{
		quotes = quotes_checking(tmp->arg[i][s]);
		if (quotes != 0)
		{
			remove_symbol_arguments(tmp, i, s);
			while (quotes_checking(tmp->arg[i][s]) != quotes && tmp->arg[i][s] != '\0')
			{
				s++;
			}
			remove_symbol_arguments(tmp, i, s);
		}
		else
			s++;
	}
}

int	remove_symbol(t_all *tmp, int i)
{
	int remember;
	int rem;
	int j;
	char *t_arr;

	remember = i;
	t_arr = NULL;
	j = ft_strlen(tmp->str) - 1;
	rem = j;
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
	t_arr[j] = '\0';
	j = -1;
	while(++j < remember)
		t_arr[j] = tmp->str[j];
	while(tmp->str[++i] != '\0' && j < rem)
	{
		t_arr[j] = tmp->str[i];
		j++;
	}
	free(tmp->str);
	tmp->str = NULL;
	tmp->str = t_arr;
	if (tmp->str[remember] == '\0')
		remember--;
	return (remember);
}
