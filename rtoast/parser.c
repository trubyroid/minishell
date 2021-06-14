#include "shell.h"

void	command_name(t_all *tmp)
{
	int	i;
	int colnum;
	int	q;

	i = 0;
	i = skipping_spaces(tmp, i);
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
	arg(tmp, i);
}

void	arg(t_all *tmp, int i)
{
	int		q;
	int		colnum;

	while (tmp->str[i] != '\0')
	{
		i = skipping_spaces(tmp, i);
		q = quotes_checking(tmp->str[i]);
		if (block_checking(tmp->str[i]) == 1)
			break ;
		if (q != 0)
			colnum = amount_of_elements(tmp, ++i, q);
		else
			colnum = amount_of_elements(tmp, i, 0);
		i = malloc_arg(tmp, i, colnum);
		if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
			i++;
	}
}

int	malloc_arg(t_all *tmp, int i, int num)
{
	if (tmp->arg == NULL)
		i = creating_the_first_argument(tmp, i, num);
	else
		i = creating_next_argument(tmp, i, num);
	return (i);
}
