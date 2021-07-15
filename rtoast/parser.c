#include "../shell.h"

void	command_name(t_all *tmp, t_env *lst, int i)
{
	int colnum;
	int	q;
	int count;

	if (tmp->str[0] == '\0')
	{
		tmp->str = NULL;
		return ;
	}
	//i = tmp->redirect_i;
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
	if (tmp->command_name)
		creating_name_argument(tmp);
	if (tmp->str[i] == '|')
	{
		tmp->baby_pipe = init_baby(tmp->baby_pipe, tmp);
		command_name(tmp->baby_pipe, lst, ++i);
	}
	arg(tmp, i, lst);
}

void	arg(t_all *tmp, int i, t_env *lst)
{
	int		colnum;

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
			colnum = argc_amount_of_elements(tmp, i);
			if (colnum == 0)
				break ;
			i = creating_next_argument(tmp, i, colnum, lst);
			if (tmp->str[i] == '\"' || tmp->str[i] == '\'')
				i++;
		}
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
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
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

	count = -1;
	new_arg = (char **)malloc(sizeof(char *) * (tmp->num_arg + 2));
	while (++count < tmp->num_arg)
		new_arg[count] = tmp->arg[count];
	free(tmp->arg);
	tmp->arg = new_arg;
	tmp->arg[tmp->num_arg + 1] = NULL;
	tmp->arg[tmp->num_arg] = tmp->file_name;
	tmp->num_arg++;
}

void for_bash(t_all *tmp)
{
	int i;
	int j;
	char *temp;

	i = 0;
	j = 2;
	if (tmp->command_name[i] == '.' && tmp->command_name[i + 1] == '/')
	{
		temp = (char *)malloc(sizeof(char) * (ft_strlen(tmp->arg[0]) - 1));
		while (tmp->arg[0][j] != '\0')
		{
			temp[i] = tmp->arg[0][j];
			i++;
			j++;
		}
		temp[i] = '\0';
		free(tmp->arg[0]);
		tmp->arg[0] = temp;
		free(tmp->command_name);
		tmp->command_name = (char *)malloc(sizeof(char) * 3);
		tmp->command_name[0] = '.';
		tmp->command_name[1] = '/';
		tmp->command_name[2] = '\0';
	}
	if (tmp->command_name[i] == '.' && tmp->command_name[i + 1] == '.' && tmp->command_name[i + 2])
	{
		temp = (char *)malloc(sizeof(char) * (ft_strlen(tmp->arg[0]) - 1));
		j = 3;
		while (tmp->arg[0][j] != '\0')
		{
			temp[i] = tmp->arg[0][j];
			i++;
			j++;
		}
		temp[i] = '\0';
		free(tmp->arg[0]);
		tmp->arg[0] = temp;
		free(tmp->command_name);
		tmp->command_name = (char *)malloc(sizeof(char) * 3);
		tmp->command_name[0] = '.';
		tmp->command_name[1] = '.';
		tmp->command_name[2] = '/';
		tmp->command_name[3] = '\0';
	}
}

t_all *init_baby(t_all *baby, t_all *tmp)
{
	baby = (t_all *)malloc(sizeof(t_all));

	baby->str = (ft_strdup(tmp->str));
	baby->baby_pipe = NULL;
	baby->fd_out = 1;
	baby->fd_in = 0;
	baby->arg = NULL;
	baby->num_arg = 0;
	baby->command_name = NULL;
	baby->file_name = NULL;
	baby->redirect_i = 0;
	return (baby);
}

