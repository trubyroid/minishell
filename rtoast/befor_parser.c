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
