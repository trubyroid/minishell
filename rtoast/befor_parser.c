#include "../shell.h"

void	error(int i)
{
	i = 4;
	printf("Error");
	exit(1);
}

void	prepars(t_all *tmp)
{
	int i;

	i = 0;
	tmp->fd_out = 1;
	tmp->fd_in = 0;
	tmp->arg = NULL;
	tmp->num_arg = 0;
	tmp->command_name = NULL;
	tmp->file_name = NULL;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == ';' && tmp->str[i + 1] == ';')
			error(1);
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '<' && tmp->str[i + 2] == '<')
			error(1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '>' && tmp->str[i + 2] == '>')
			error(1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '<')
			error(1);
		if (tmp->str[i] == '<' && tmp->str[i + 1] == '>')
			error(1);
		i++;
	}
	if (i > 0 && tmp->str[i - 1] == '\\')
		error(1);
	tmp->redirect_i = 0;
	if (i > 0)
	{
		redirect_pars(tmp);
		dollar_parser(tmp);
	}
}

// int		special_dollar(t_all *tmp, int i)
// {
// 	if (tmp->str[i] == '$' && (tmp->str[i + 1] == '!' || tmp->str[i + 1] == '$' || tmp->str[i + 1] == '*'))
// 	{
// 		i = remove_symbol(tmp, i);
// 		i = remove_symbol(tmp, i);
// 	}
// 	if (tmp->str[i] == '$' && (tmp->str[i + 1] == '#' || tmp->str[i + 1] == '@' || tmp->str[i + 1] == '-'))
// 	{
// 		i = remove_symbol(tmp, i);
// 		i = remove_symbol(tmp, i);
// 	}
// 	if(tmp->str[i] == '$' && ((tmp->str[i + 1] >= '0' && tmp->str[i + 1] <= '9') && tmp->str[i + 2] == ' '))
// 	{
// 		i = remove_symbol(tmp, i);
// 		i = remove_symbol(tmp, i);
// 	}
// 	if (tmp->str[i] == '$' && (check_for_dollar(tmp->str[i + 1]) != 0))
// 		i = i + 2;
// 	return (i);
// }

void	dollar_parser(t_all *tmp)
{
	int i;

	i = 0;
	while(tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '\'')
		{
			i++;
			while (tmp->str[i] != '\'' && tmp->str[i] != '\0')
				i++;
		}
		if (tmp->str[i] == '$' && (tmp->str[i + 1] == '!' || tmp->str[i + 1] == '$' || tmp->str[i + 1] == '*'))
		{
			i = remove_symbol(tmp, i);
			i = remove_symbol(tmp, i);
		}
		if (tmp->str[i] == '$' && (tmp->str[i + 1] == '#' || tmp->str[i + 1] == '@' || tmp->str[i + 1] == '-'))
		{
			i = remove_symbol(tmp, i);
			i = remove_symbol(tmp, i);
		}
		if(tmp->str[i] == '$' && ((tmp->str[i + 1] >= '0' && tmp->str[i + 1] <= '9') && tmp->str[i + 2] == ' '))
		{
			i = remove_symbol(tmp, i);
			i = remove_symbol(tmp, i);
		}
		if (tmp->str[i] == '$' && (check_for_dollar(tmp->str[i + 1]) != 0))
			i++;
		if(tmp->str[i] == '$')
			continue ;
		if (tmp->str[i] != '\0')
			i++;
	}

	printf("---->%s\n", tmp->str);
}

void	redirect_pars(t_all *tmp)
{
	int i;

	i = 0;
	i = skipping_spaces(tmp, i);
	if (tmp->str[i] == '>' || tmp->str[i] == '<')
		tmp->redirect_i = redirect(tmp, i);
}

int	remove_symbol(t_all *tmp, int i)
{
	int remember;
	int rem;
	int j;
	char *t_arr;

	remember = i;
	t_arr = NULL;
	j = ft_strlen(tmp->str) - 1;
	rem = j;
	t_arr = (char *)malloc(sizeof(char) * (j + 1 ));
	t_arr[j] = '\0';
	j = -1;
	while(++j < remember)
		t_arr[j] = tmp->str[j];
	while(tmp->str[++i] != '\0' && j < rem)
	{
		t_arr[j] = tmp->str[i];
		j++;
	}
	free(tmp->str);
	tmp->str = NULL;
	tmp->str = t_arr;
	if (tmp->str[remember] == '\0')
		remember--;
	printf("---->%d|%s|\n", remember, tmp->str);
	return (remember);
}
