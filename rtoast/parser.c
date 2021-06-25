#include "../shell.h"

void	command_name(t_all *tmp)
{
	int	i;
	int colnum;
	int	q;

	i = 0;
	i = skipping_spaces(tmp, i);
	if (tmp->str[i] == '\\')
		i++;
	q = quotes_checking(tmp->str[i]);
	if (q != 0)
		colnum = amount_of_elements(tmp, ++i, q);
	else
		colnum = amount_of_elements(tmp, i, 0);
	tmp->command_name = (char *)malloc(sizeof(char) * (colnum + 1));
	tmp->command_name[colnum] = '\0';
	q = 0;
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->command_name[q] = tmp->str[i];
		i++;
		q++;
	}
	if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
		i++;
	creating_name_argument(tmp);
	arg(tmp, i);
}

void	arg(t_all *tmp, int i)
{
	int		colnum;

	while (tmp->str[i] != '\0')
	{
		i = skipping_spaces(tmp, i);
		if (block_checking(tmp->str[i]) == 1)
			break ;
		colnum = argc_amount_of_elements(tmp, i);
		i = creating_next_argument(tmp, i, colnum);
		if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
			i++;
	}
}

int		remove_symbol_arguments(t_all *tmp, int i, int s)
{
	int remember;
	int j;
	char *t_arr;

	j = 0;
	remember = s;
	t_arr = NULL;
	while (tmp->arg[i][j] != '\0')
		j++;
	j--;
	t_arr = (char *)malloc(sizeof(char) * (j));
	t_arr[j] = '\0';
	j = -1;
	while(++j < remember)
		t_arr[j] = tmp->arg[i][j];
	s = j;
	while(tmp->arg[i][++j] != '\0')
	{
		t_arr[s] = tmp->arg[i][j];
		s++;
	}
	free(tmp->arg[i]);
	tmp->arg[i] = t_arr;
	return (remember);
}
