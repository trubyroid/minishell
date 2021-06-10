#include "shell.h"

// int malloc_arg(t_all *tmp, int i, t_add *add)
// {
// 	int j;
// 	int count;
// 	char **new_arg;

// 	j = 0;
// 	count = -1;
// 	while (tmp->str[i] != ' ' && block(tmp, i) == 0)
// 	{
// 		j++;
// 		i++;
// 	}
// 	if (tmp->arg == NULL)
// 	{
// 		tmp->arg = (char**)malloc(sizeof(char*));
// 		tmp->arg[add->num] = (char*)malloc(sizeof(char) * j + 1);
// 		tmp->arg[add->num][j + 1] = '\0';
// 		i = i - j;
// 		j = 0;
// 		while (tmp->str[i] != ' ' && block(tmp, i) == 0)
// 		{
// 			tmp->arg[add->num][j] = tmp->str[i];
// 			i++;
// 			j++;
// 		}
// 	}
// 	else
// 	{
// 		new_arg = (char**)malloc(sizeof(char*) * add->num);
// 		while (++count < add->num)
// 			new_arg[count] = tmp->arg[count];
// 		free(tmp->arg);
// 		count = -1;
// 		tmp->arg = (char**)malloc(sizeof(char*) * (add->num + 1));
// 		while (++count < add->num)
// 			tmp->arg[count] = new_arg[count];
// 		add->num++;
// 		tmp->arg[add->num] = (char*)malloc(sizeof(char) * j + 1);
// 		tmp->arg[add->num][j + 1] = '\0';
// 		i = i - j;
// 		j = 0;
// 		while (tmp->str[i] != ' ' && block(tmp, i) == 0)
// 		{
// 			tmp->arg[add->num][j] = tmp->str[i];
// 			i++;
// 			j++;
// 		}
// 		free(new_arg);
// 	}
// 	return(i);
// }

// int block(t_all *tmp, int i)
// {
// 	if (tmp->str[i] == '\0')
// 		return(-1);
// 	if (tmp->str[i] == '|')
// 		return(-1);
// 	if (tmp->str[i] == ';')
// 		return(-1);
// 	if (tmp->str[i] == '<')
// 		return(-1);
// 	if (tmp->str[i] == '>')
// 		return(-1);
// 	return(0);
// }

void command_name(t_all *tmp)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while ((character_checking(tmp->str[i])) == 1)
		i++;
	while (tmp->str[i] != '\0' && (character_checking(tmp->str[i]) == 0))
	{
		j++;
		i++;
	}
	tmp->command_name = (char *)malloc(sizeof(char) * (j + 1));
	tmp->command_name[j] = '\0';
	i = i - j;
	j = 0;
	while (tmp->str[i] != '\0' && character_checking(tmp->str[i]) == 0)
	{
		tmp->command_name[j] = tmp->str[i];
		i++;
		j++;
	}
	// arg(tmp, i);
}

// void arg(t_all *tmp, int i)
// {
// 	t_add *add;

// 	add = (t_add *)malloc(sizeof(add));
// 	add->num = 0;
// 	while (tmp->str[i] != '\0')
// 	{
// 		while (tmp->str[i] == ' ')
// 			i++;
// 		if (block(tmp, i) == -1)
// 			break ;///
// 		i = malloc_arg(tmp, i, add);
// 	}
// 	free(add);
// }
