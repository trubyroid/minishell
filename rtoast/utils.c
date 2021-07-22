#include "../shell.h"

int	skipping_spaces(t_all *tmp, int i)
{
	while (tmp->str[i] == ' ')
		i++;
	return (i);
}

int	quotes_checking(char symbol)
{
	int	result;

	result = 0;
	if (symbol == '\'')
		result = 1;
	if (symbol == '\"')
		result = 2;
	return (result);
}

void	add_fd(t_all *tmp, int fd)
{
	int	*temp;
	int	i;

	i = -1;
	if (tmp->massiv_fd == NULL)
	{
		tmp->massiv_fd = (int *)malloc(sizeof(int) * 1);
		tmp->massiv_fd[0] = fd;
		tmp->colnum_fd = 1;
	}
	else
	{
		temp = (int *)malloc(sizeof(int) * (tmp->colnum_fd + 1));
		while (++i < tmp->colnum_fd)
			temp[i] = tmp->massiv_fd[i];
		free(tmp->massiv_fd);
		tmp->massiv_fd = temp;
	}
}

int	amout_elements_redirect(t_all *tmp, int j)
{
	int	count;

	count = 0;
	while (tmp->str[j] != ' ' && block_checking(tmp->str[j]) == 0)
	{
		j++;
		count++;
	}
	return (count);
}

void	free_file_name(t_all *tmp)
{
	free(tmp->file_name);
	tmp->file_name = NULL;
}
