#include "../shell.h"

void	remove_quotes(t_all *tmp, int i)
{
	int	s;
	int	quotes;

	s = 0;
	while (tmp->arg[i][s] != '\0')
	{
		quotes = quotes_checking(tmp->arg[i][s]);
		if (quotes != 0)
		{
			remove_symbol_arguments(tmp, i, s);
			while (quotes_checking(tmp->arg[i][s]) != quotes && \
					tmp->arg[i][s] != '\0')
				s++;
			if (tmp->arg[i][s] != '\0')
				remove_symbol_arguments(tmp, i, s);
		}
		if (tmp->arg[i][s] != '\0')
			s++;
	}
}

int	remove_symbol(t_all *tmp, int i)
{
	int		remember;
	int		rem;
	int		j;
	char	*t_arr;

	remember = i;
	t_arr = NULL;
	j = ft_strlen(tmp->str) - 1;
	rem = j;
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
	t_arr[j] = '\0';
	j = -1;
	while (++j < remember)
		t_arr[j] = tmp->str[j];
	while (tmp->str[++i] != '\0' && j < rem)
	{
		t_arr[j] = tmp->str[i];
		j++;
	}
	free(tmp->str);
	tmp->str = NULL;
	tmp->str = t_arr;
	if (tmp->str[remember] == '\0')
		remember--;
	return (remember);
}

int	remove_dollar(t_all *tmp, int i)
{
	i = remove_symbol(tmp, i);
	i = remove_symbol(tmp, i);
	add_spase(i, tmp);
	return (i);
}

int	remove_symbol_arguments(t_all *tmp, int i, int s)
{
	int		remember;
	int		j;
	char	*t_arr;

	j = -1;
	remember = s;
	t_arr = NULL;
	j = ft_strlen(tmp->arg[i]) - 1;
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
	t_arr[j] = '\0';
	while (++j < remember)
		t_arr[j] = tmp->arg[i][j];
	s = j;
	while (tmp->arg[i][++j] != '\0')
	{
		t_arr[s] = tmp->arg[i][j];
		s++;
	}
	free(tmp->arg[i]);
	tmp->arg[i] = t_arr;
	if (remember == '\0')
		remember--;
	return (remember);
}

int	remove_symbol_name(t_all *tmp, int i)
{
	int		remember;
	int		rem;
	int		j;
	char	*t_arr;

	remember = i;
	t_arr = NULL;
	j = ft_strlen(tmp->command_name) - 1;
	rem = j;
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
	t_arr[j] = '\0';
	j = -1;
	while (++j < remember)
		t_arr[j] = tmp->command_name[j];
	while (tmp->command_name[++i] != '\0' && j < rem)
	{
		t_arr[j] = tmp->command_name[i];
		j++;
	}
	free(tmp->command_name);
	tmp->command_name = NULL;
	tmp->command_name = t_arr;
	if (tmp->command_name[remember] == '\0')
		remember--;
	return (remember);
}
