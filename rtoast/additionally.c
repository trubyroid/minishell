#include "../shell.h"

int	amount_of_elements(t_all *tmp, int i)
{
	int	colnum;
	int	q;

	colnum = 0;
	while (block_checking(tmp->str[i]) == 0 && tmp->str[i] != ' ')
	{
		q = quotes_checking(tmp->str[i]);
		if (q != 0)
		{
			i++;
			colnum++;
			while (quotes_checking(tmp->str[i]) != q && tmp->str[i] != '\0')
			{
				i++;
				colnum++;
			}
		}
		if (tmp->str[i] != '\0')
		{
			i++;
			colnum++;
		}
	}
	return (colnum);
}

int	argc_amount_of_elements(t_all *tmp, int i)
{
	int	colnum;
	int	quotes;

	colnum = 0;
	while (tmp->str[i] != ' ' && block_checking(tmp->str[i]) == 0)
	{
		quotes = quotes_checking(tmp->str[i]);
		if (quotes != 0)
		{
			i++;
			colnum++;
			while (quotes_checking(tmp->str[i]) != quotes \
					&& tmp->str[i] != '\0')
			{
				i++;
				colnum++;
			}
		}
		i++;
		colnum++;
	}
	return (colnum);
}

int	block_checking(char symbol)
{
	if (symbol == '\0')
		return (1);
	if (symbol == '|')
		return (3);
	if (symbol == '>')
		return (2);
	if (symbol == '<')
		return (2);
	return (0);
}

void	creating_name_argument(t_all *tmp)
{
	tmp->num_arg = 1;
	tmp->arg = (char **)malloc((sizeof(char *)) * 2);
	if(ft_strcmp(tmp->command_name, "$?") == 0)
		tmp->arg[0] = ft_itoa(g_status);
	else
		tmp->arg[0] = ft_strdup(tmp->command_name);
	tmp->arg[1] = NULL;
}

int	creating_next_argument(t_all *tmp, int i, int colnum, t_env *lst)
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
	search_dollar(tmp, lst);
	remove_quotes(tmp, tmp->num_arg);
	tmp->num_arg++;
	return (i);
}
