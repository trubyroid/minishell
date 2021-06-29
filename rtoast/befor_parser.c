#include "../shell.h"

void	error(int i)
{
	i = 4;
	printf("Error");
	exit(1);
}

void	prepars(t_all *tmp, char **env)
{
	int i;

	i = 0;
	tmp->fd_out = 1;
	tmp->fd_in = 0;
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
	if (tmp->str[i - 1] == '\\')
		error(1);
	tmp->redirect_i = 0;
	redirect_pars(tmp);
	dollar_parser(tmp, env);
}

int		special_dollar(t_all *tmp, int i)
{
	i++;
	if (tmp->str[i] == '*')
	{
		i = remove_symbol(tmp, i);
		i = remove_symbol(tmp, i);
	}
	return (i);
}

void	dollar_parser(t_all *tmp, char **env)
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
		if (tmp->str[i] == '$')
		{
			i = special_dollar(tmp, i);
		}
		if (tmp->str[i] == '$')
			dollar_make(tmp, i + 1, env);
		if (tmp->str[i] != '\0')
			i++;
	}
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
	int j;
	char *t_arr;

	j = 0;
	remember = i;
	t_arr = NULL;
	while (tmp->str[j] != '\0')
		j++;
	j--;
	t_arr = (char *)malloc(sizeof(char) * (j + 1 ));
	t_arr[j] = '\0';
	j = -1;
	while(++j < remember)
		t_arr[j] = tmp->str[j];
	i++;
	while(tmp->str[++i] != '\0')
	{
		t_arr[j] = tmp->str[i];
		j++;
	}
	free(tmp->str);
	tmp->str = NULL;
	tmp->str = t_arr;
	printf("%s\n", tmp->str);
	if (tmp->str[remember] == '\0')
		remember--;
	return (remember);
}
