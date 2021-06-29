#include "../shell.h"

void	command_name(t_all *tmp)
{
	int	i;
	int colnum;
	int	q;
	int count;

	i = tmp->redirect_i;
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
	count = 0;
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->command_name[count] = tmp->str[i];
		i++;
		count++;
	}
	if (q != 0)
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
		if (block_checking(tmp->str[i]) == 2)
			i = redirect(tmp, i);
		colnum = argc_amount_of_elements(tmp, i);
		i = creating_next_argument(tmp, i, colnum);
		if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
			i++;
	}
	if (tmp->arg[1] == NULL && tmp->file_name)
		creating_file_name_elem(tmp);
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
	if (remember == '\0')
		remember--;
	return (remember);
}

void	creating_file_name_elem(t_all *tmp)
{
	char	**new_arg;
	int		count;

	count = 0;
	new_arg = (char **)malloc(sizeof(char *) * (tmp->num_arg + 2));
	while (++count < tmp->num_arg)
		new_arg[count] = tmp->arg[count];
	free(tmp->arg);
	tmp->arg = new_arg;
	tmp->arg[tmp->num_arg + 1] = NULL;
	tmp->arg[tmp->num_arg] = tmp->file_name;
	tmp->num_arg++;
}
