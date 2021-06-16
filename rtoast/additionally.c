#include "../shell.h"

int	amount_of_elements(t_all *tmp, int i, int quotes)
{
	int colnum;

	colnum = 0;
	if (quotes != 0)
		while (quotes_checking(tmp->str[i]) != quotes)
		{
			colnum++;
			i++;
		}
	else
	{
		while (block_checking(tmp->str[i]) == 0 && tmp->str[i] != ' ')
		{
			colnum++;
			i++;
		}
	}
	return (colnum);
}

int	skipping_spaces(t_all *tmp, int i)
{
	while (tmp->str[i] == ' ')
		i++;
	return (i);
}

int	quotes_checking(char symbol)
{
	int	result;

	result = 0;
	if (symbol == '\'')
		result = 1;
	if (symbol == '\"')
		result = 2;
	return (result);
}

int	block_checking(char symbol)
{
	if (symbol == '\0')
		return (1);
	if (symbol == '|')
		return (1);
	if (symbol == '>')
		return (1);
	if (symbol == '<')
		return (1);
	return (0);
}

int	creating_the_first_argument(t_all *tmp, int i, int colnum)
{
	int j;

	j = 0;
	tmp->num_arg = 1;
	tmp->arg = (char **)malloc((sizeof(char *)) * 3);
	tmp->arg[0] = tmp->command_name;
	tmp->arg[tmp->num_arg] = (char *)malloc(sizeof(char) * (colnum + 1));
	tmp->arg[tmp->num_arg + 1] = NULL;
	tmp->arg[tmp->num_arg][colnum] = '\0';
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->arg[tmp->num_arg][j] = tmp->str[i];
		i++;
		j++;
	}
	tmp->num_arg++;
	return (i);
}

int	creating_next_argument(t_all *tmp, int i, int colnum)
{
	int		count;
	int		j;
	char	**new_arg;

	count = -1;
	j = 0;
	new_arg = (char **)malloc(sizeof(char *) * (tmp->num_arg + 2));
	while (++count < tmp->num_arg)
		new_arg[count] = tmp->arg[count];
	free(tmp->arg);
	tmp->arg = new_arg;
	tmp->arg[tmp->num_arg + 1] = NULL;
	tmp->arg[tmp->num_arg] = (char *)malloc(sizeof(char) * (colnum + 1));
	tmp->arg[tmp->num_arg][colnum] = '\0';
	colnum = i + colnum;
	while (i < colnum)
	{
		tmp->arg[tmp->num_arg][j] = tmp->str[i];
		i++;
		j++;
	}
	tmp->num_arg++;
	return (i);
}