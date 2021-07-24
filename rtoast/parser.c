#include "../shell.h"

void	command_name(t_all *tmp, t_env *lst, int i)
{
	int	colnum;
	int	q;

	if (tmp->str[0] == '\0')
	{
		tmp->str = NULL;
		return ;
	}
	if (i == 0)
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
	create(tmp, i, colnum, lst);
}

void	create(t_all *tmp, int i, int colnum, t_env *lst)
{
	int	count;

	count = 0;
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->command_name[count] = tmp->str[i];
		i++;
		count++;
	}
	if (quotes_checking(tmp->str[i] != 0))
		i++;
	if (tmp->command_name)
		creating_name_argument(tmp);
	if (tmp->str[i] == '|')
	{
		tmp->baby_pipe = init_baby(tmp->baby_pipe, tmp);
		command_name(tmp->baby_pipe, lst, ++i);
	}
	quotes_name(tmp);
	arg(tmp, i, lst);
}

void	arg(t_all *tmp, int i, t_env *lst)
{
	for_bash(tmp);
	while (tmp->str[i] != '\0')
	{
		i = skipping_spaces(tmp, i);
		if (block_checking(tmp->str[i]) == 1)
			break ;
		if (block_checking(tmp->str[i]) == 3)
		{
			tmp->baby_pipe = init_baby(tmp->baby_pipe, tmp);
			command_name(tmp->baby_pipe, lst, ++i);
		}
		if (block_checking(tmp->str[i]) == 2)
			i = redirect(tmp, i);
		else
		{
			i = arg_create(tmp, i, lst);
			if (i == -1)
				break ;
		}
	}
	if (tmp->arg[1] == NULL && tmp->file_name)
		creating_file_name_elem(tmp);
}

int	arg_create(t_all *tmp, int i, t_env *lst)
{
	int	colnum;

	colnum = argc_amount_of_elements(tmp, i);
	if (colnum == 0)
		return (-1);
	i = creating_next_argument(tmp, i, colnum, lst);
	if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
		i++;
	return (i);
}
