#include "shell.h"








void	command_name(t_all *tmp)
{
	int	i;
	int colnum;
	int	q;

	i = 0;
	skipping_spaces(tmp, i);
	q = quotes_checking(tmp->str[i]);
	if (q != 0)
		colnum = amount_of_elements(tmp, ++i, q);
	else
		colnum = amount_of_elements(tmp, i, 0);
	tmp->command_name = (char *)malloc(sizeof(char) * (colnum + 1));
	tmp->command_name[colnum] = '\0';
	q = 0;
	while (i < (i + colnum))
	{
		tmp->command_name[q] = tmp->str[i];
		i++;
		q++;
	}
	arg(tmp, i);
}
