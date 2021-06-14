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
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->command_name[q] = tmp->str[i];
		i++;
		q++;
	}
	//arg(tmp, i);
}

// void	arg(t_all *tmp, int i)
// {
// 	t_add	*add;

// 	add = (t_add *)malloc(sizeof(add));
// 	while (tmp->str[i] != '\0')
// 	{
// 		while ((character_checking(tmp->str[i])) == 1)
// 			i++;
// 		if (block(tmp, i) == 1)
// 			break ;
// 		i = malloc_arg(tmp, i, add);
// 	}
// 	free(add);
// }

// int	malloc_arg(t_all *tmp, int i, t_add *add)
// {
// 	int	j;

// 	j = 0;
// 	while ((character_checking(tmp->str[i])) == 0 && block(tmp, i) == 0)
// 	{
// 		j++;
// 		i++;
// 	}
// 	printf("%d\n", i);
// 	if (tmp->arg == NULL)
// 		i = creating_the_first_argument(tmp, add, i, j);
// 	else
// 		i = creating_next_argument(tmp, add, i, j);
// 	return (i);
// }
