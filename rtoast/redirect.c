#include "../shell.h"

///massiv int fd
int		redirect(t_all *tmp, int i)
{
	int j;
	int count;
	char *file_name;

	count = 0;
	if (tmp->str[i] == '>')
		i++;
	if (tmp->str[i] == '>')
	{
		i++;
		return (double_redirect(tmp, i));
	}
	i = skipping_spaces(tmp, i);
	j = i;
	while (tmp->str[j] != ' ' && tmp->str[j] != '\0')
	{
		j++;
		count++;
	}
	file_name = (char *)malloc(sizeof(char) * count);
	count = 0;
	while (i < j)
	{
		file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file_name);
	i = skipping_spaces(tmp, i);
	return (i);
}

int		double_redirect(t_all *tmp, int i)
{
	int j;
	int count;
	char *file_name;

	count = 0;
	i = skipping_spaces(tmp, i);
	j = i;
	while (tmp->str[j] != ' ' && tmp->str[j] != '\0')
	{
		j++;
		count++;
	}
	file_name = (char *)malloc(sizeof(char) * count);
	count = 0;
	while (i < j)
	{
		file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file_name);
	return (i);
}