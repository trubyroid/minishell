#include "../shell.h"

void	quotes_for_redirect(t_all *tmp)
{
	int	i;
	int	q;

	i = 0;
	while (tmp->file_name[i] != '\0')
	{
		q = quotes_checking(tmp->file_name[i]);
		if (q != 0)
		{
			i = remove_symbol_redirect(tmp, i);
			while (quotes_checking(tmp->file_name[i]) != q)
				i++;
			i = remove_symbol_redirect(tmp, i);
		}
		else
			i++;
	}
}

int	remove_symbol_redirect(t_all *tmp, int i)
{
	int		remember;
	int		j;
	char	*t_arr;

	remember = i;
	t_arr = NULL;
	j = ft_strlen(tmp->file_name) - 1;
	t_arr = (char *)malloc(sizeof(char) * (j + 1));
	t_arr[j] = '\0';
	j = -1;
	while (++j < remember)
		t_arr[j] = tmp->file_name[j];
	while (tmp->file_name[++i] != '\0')
	{
		t_arr[j] = tmp->file_name[i];
		j++;
	}
	free(tmp->file_name);
	tmp->file_name = NULL;
	tmp->file_name = t_arr;
	return (remember);
}
