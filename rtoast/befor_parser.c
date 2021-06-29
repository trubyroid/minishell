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
