#include "shell.h"

void	command_name(t_all *tmp)
{
	int	j;
	int	i;

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
	arg(tmp, i);
}

void	arg(t_all *tmp, int i)
{
	t_add	*add;

	add = (t_add *)malloc(sizeof(add));
	while (tmp->str[i] != '\0')
	{
		while ((character_checking(tmp->str[i])) == 1)
			i++;
		if (block(tmp, i) == 1)
			break ;
		i = malloc_arg(tmp, i, add);
	}
	free(add);
}

int	malloc_arg(t_all *tmp, int i, t_add *add)
{
	int	j;

	j = 0;
	while ((character_checking(tmp->str[i])) == 0 && block(tmp, i) == 0)
	{
		j++;
		i++;
	}
	if (tmp->arg == NULL)
		i = creating_the_first_argument(tmp, add, i, j);
	else
		i = creating_next_argument(tmp, add, i, j);
	return (i);
}
