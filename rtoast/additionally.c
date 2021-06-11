#include "shell.h"

int	character_checking(char symbol)
{
	int	result;

	result = 0;
	if (symbol == ' ')
		result = 1;
	if (symbol == '\'')
		result = 1;
	if (symbol == '\"')
		result = 1;
	return (result);
}

int	block(t_all *tmp, int i)
{
	if (tmp->str[i] == '\0')
		return (1);
	if (tmp->str[i] == '|')
		return (1);
	if (tmp->str[i] == '<')
		return (1);
	if (tmp->str[i] == '>')
		return (1);
	return (0);
}

int	creating_the_first_argument(t_all *tmp, t_add *add, int i, int j)
{
	add->num = 0;
	tmp->arg = (char **)malloc(sizeof(char *));
	tmp->arg[add->num] = (char *)malloc(sizeof(char) * (j + 1));
	tmp->arg[add->num][j] = '\0';
	i = i - j;
	j = 0;
	while ((character_checking(tmp->str[i])) == 0 && block(tmp, i) == 0)
	{
		tmp->arg[add->num][j] = tmp->str[i];
		i++;
		j++;
	}
	add->num++;
	return (i);
}

int	creating_next_argument(t_all *tmp, t_add *add, int i, int j)
{
	int		count;
	char	**new_arg;

	count = -1;
	new_arg = (char **)malloc(sizeof(char *) * (add->num + 1));
	while (++count < add->num)
		new_arg[count] = tmp->arg[count];
	free(tmp->arg);
	tmp->arg = new_arg;
	tmp->arg[add->num] = (char *)malloc(sizeof(char) * (j + 1));
	tmp->arg[add->num][j] = '\0';
	i = i - j;
	j = 0;
	while ((character_checking(tmp->str[i])) == 0 && block(tmp, i) == 0)
	{
		tmp->arg[add->num][j] = tmp->str[i];
		i++;
		j++;
	}
	add->num++;
	return (i);
}
