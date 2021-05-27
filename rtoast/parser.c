#include "shell.h"

void error(int i)
{
	printf("Error");
	exit(1);
}

void prepars(t_all *tmp)
{
	int i;
	int two_e;
	int one_e;

	i = 0;
	two_e = 0;
	one_e = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == '"')
			two_e++;
		if (tmp->str[i] == '\'')
			one_e++;
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
	if (two_e % 2 != 0)
		error(1);
	if (one_e % 2 != 0)
		error(1);
	if (tmp->str[i - 1] == '\\')
		error(1);
}

void start(t_all *tmp)
{
	int i;

	i = 0;
	while (tmp->str[i] != '\0')
	{
		if (tmp->str[i] == ' ' || tmp->str[i] == '	')
			i++;
		else
			break ;
	}
	command_name(tmp, i);
}

void command_name(t_all *tmp, int i)
{
	int j;

	j = 0;
	if (tmp->str[i] == '\'' || tmp->str[i] == '\\')
		i++;
	while (tmp->str[i] != '\0' && tmp->str[i] != '\'' && tmp->str[i] != ' ')
	{
		j++;
		i++;
	}
	tmp->command_name = (char *)malloc(j * sizeof(char *) + 1);
	tmp->command_name[j + 1] = '\0';
	i = i - j;
	j = 0;
	while (tmp->str[i] != '\'' && tmp->str[i] != ' ')
	{
		tmp->command_name[j] = tmp->str[i];
		i++;
		j++;
	}
}

void arg(t_all *tmp, int i)
{
	int j;

	j = 0;
	while (tmp->str[i] == '\'' || tmp->str[i] == ' ')
		i++;
	while (tmp->str[i] == '\'' || tmp->str[i] == ' ')
	{
		j++;
		i++;
	}
}
