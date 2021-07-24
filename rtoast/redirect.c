#include "../shell.h"

int	redirect(t_all *tmp, int i)
{
	if (tmp->str[i] == '>' && tmp->str[i + 1] != '>')
	{
		i++;
		return (single_redirect(tmp, i));
	}
	if (tmp->str[i] == '>' && tmp->str[i + 1] == '>')
	{
		i = i + 2;
		return (double_redirect(tmp, i));
	}
	if (tmp->str[i] == '<' && tmp->str[i + 1] != '<')
	{
		i++;
		return (reverse_redirect(tmp, i));
	}
	if (tmp->str[i] == '<' && tmp->str[i + 1] == '<')
	{
		i = i + 2;
		return (reverse_double_redirect(tmp, i));
	}
	return (i);
}

int	single_redirect(t_all *tmp, int i)
{
	int		j;
	int		count;
	char	*file_name;

	tmp->fd_in = 0;
	i = skipping_spaces(tmp, i);
	j = i;
	count = amout_elements_redirect(tmp, j);
	j = j + count;
	file_name = (char *)malloc(sizeof(char) * count);
	file_name[count] = '\0';
	count = 0;
	while (i < j)
	{
		file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp->fd_out != -1)
		add_fd(tmp, tmp->fd_out);
	free(file_name);
	i = skipping_spaces(tmp, i);
	return (i);
}

int	double_redirect(t_all *tmp, int i)
{
	int		j;
	int		count;
	char	*file_name;

	i = skipping_spaces(tmp, i);
	j = i;
	count = amout_elements_redirect(tmp, j);
	j = j + count;
	file_name = (char *)malloc(sizeof(char) * count);
	file_name[count] = '\0';
	count = 0;
	while (i < j)
	{
		file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_out = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmp->fd_out != -1)
		add_fd(tmp, tmp->fd_out);
	free(file_name);
	i = skipping_spaces(tmp, i);
	return (i);
}

int	reverse_redirect(t_all *tmp, int i)
{
	int	j;
	int	count;

	i = skipping_spaces(tmp, i);
	j = i;
	count = amout_elements_redirect(tmp, j);
	j = j + count;
	tmp->file_name = (char *)malloc(sizeof(char) * count + 1);
	tmp->file_name[count] = '\0';
	count = 0;
	while (i < j)
	{
		tmp->file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	if (ft_strncmp(tmp->command_name, "cat", 3) != 0)
		free_file_name(tmp);
	tmp->fd_in = open(tmp->file_name, O_RDONLY, 0644);
	if (tmp->fd_in != -1)
		add_fd(tmp, tmp->fd_in);
	i = skipping_spaces(tmp, i);
	return (i);
}

int	reverse_double_redirect(t_all *tmp, int i)
{
	char	*blok;
	int		j;
	int		count;

	i = skipping_spaces(tmp, i);
	j = i;
	count = amout_elements_redirect(tmp, j);
	j = j + count;
	blok = (char *)malloc(sizeof(char) * (count + 1));
	blok[count] = '\0';
	count = -1;
	while (i < j)
	{
		blok[++count] = tmp->str[i];
		i++;
	}
	fd_in_funk(tmp);
	get_reverse_redirect(tmp, &blok);
	tmp->file_name = ft_strdup("./.ghost");
	free(blok);
	return (i);
}
