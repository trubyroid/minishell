#include "../shell.h"

t_all	*init_baby(t_all *baby, t_all *tmp)
{
	baby = (t_all *)malloc(sizeof(t_all));
	baby->str = (ft_strdup(tmp->str));
	baby->baby_pipe = NULL;
	baby->colnum_fd = 0;
	baby->massiv_fd = NULL;
	baby->fd_out = 1;
	baby->fd_in = 0;
	baby->arg = NULL;
	baby->num_arg = 0;
	baby->command_name = NULL;
	baby->file_name = NULL;
	baby->redirect_i = 0;
	return (baby);
}

void	quotes_name(t_all *tmp)
{
	int	i;

	i = 0;
	while (tmp->command_name[i] != '\0')
	{
		if (tmp->command_name[i] == '\'' && tmp->command_name[i + 1] == '\'')
		{
			i = remove_symbol_name(tmp, i);
			i = remove_symbol_name(tmp, i);
		}
		if (tmp->command_name[i] == '\"' && tmp->command_name[i + 1] == '\"')
		{
			i = remove_symbol_name(tmp, i);
			i = remove_symbol_name(tmp, i);
		}
		else
			i++;
	}
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

void	command_slash(t_all *tmp, int i)
{
	free(tmp->command_name);
	if (i == 1)
	{
		tmp->command_name = (char *)malloc(sizeof(char) * 3);
		tmp->command_name[0] = '.';
		tmp->command_name[1] = '/';
		tmp->command_name[2] = '\0';
	}
	else
	{
		tmp->command_name = (char *)malloc(sizeof(char) * 4);
		tmp->command_name[0] = '.';
		tmp->command_name[1] = '.';
		tmp->command_name[2] = '/';
		tmp->command_name[3] = '\0';
	}
}
