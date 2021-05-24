#include "shell.h"
//prepars "", '', \, ;;, >>>, <<<, <>

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
