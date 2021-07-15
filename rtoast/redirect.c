#include "../shell.h"

int		redirect(t_all *tmp, int i)
{
	
	if (tmp->str[i] == '>' && tmp->str[i + 1] != '>')
	{
		i++;
		return(single_redirect(tmp, i));
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

int		single_redirect(t_all *tmp, int i)
{
	int j;
	int count;
	char *file_name;

	count = 0;
	tmp->fd_in = 0;
	i = skipping_spaces(tmp, i);
	j = i;
	while (tmp->str[j] != ' ' && tmp->str[j] != '\0')
	{
		j++;
		count++;
	}
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

int		reverse_redirect(t_all *tmp, int i)
{
	int j;
	int count;

	count = 0;
	i = skipping_spaces(tmp, i);
	j = i;
	while (tmp->str[j] != ' ' && tmp->str[j] != '\0')
	{
		j++;
		count++;
	}
	tmp->file_name = (char *)malloc(sizeof(char) * count + 1);
	tmp->file_name[count] = '\0';
	count = 0;
	while (i < j)
	{
		tmp->file_name[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_in = open(tmp->file_name, O_RDONLY, 0644);
	if (tmp->fd_in != -1)
		add_fd(tmp, tmp->fd_in);
	i = skipping_spaces(tmp, i);
	return (i);
}

int		reverse_double_redirect(t_all *tmp, int i)
{
	char *blok;
	char *str;
	int j;
	int count;

	i = skipping_spaces(tmp, i);
	j = i;
	count = 0;
	while (tmp->str[j] != ' ' && tmp->str[j] != '\0')
	{
		j++;
		count++;
	}
	blok = (char *)malloc(sizeof(char) * (count + 1));
	blok[count] = '\0';
	count = 0;
	while (i < j)
	{
		blok[count] = tmp->str[i];
		count++;
		i++;
	}
	tmp->fd_in = open("./.ghost", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp->fd_in != -1)
		add_fd(tmp, tmp->fd_in);
	while (get_next_line(0, &str))
	{
		if ((ft_strncmp(str, blok, ft_strlen(blok)) == 0) && ft_strlen(blok) == ft_strlen(str))
		{
			free(str);
			break ;
		}
		write(tmp->fd_in, str, ft_strlen(str));
		write(tmp->fd_in, "\n", 1);
		free(str);
	}
	tmp->file_name = ft_strdup("./.ghost");
	free(blok);
	return (i);
}

void	add_fd(t_all *tmp, int fd)
{
	int *temp;
	int i;

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
