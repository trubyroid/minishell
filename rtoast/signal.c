#include "../shell.h"

void	ctrl_c(int i)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K\n", 6);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_slash(int i)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "\e[0K", 5);
}

void	conrol_d(void)
{
	write(1, "\033[3;1m", 7);
	write(1, ANSI_COLOR_MAGENTA"\e[1A\e[11Cexit\n"ANSI_COLOR_RESET, 19);
	exit(0);
}

void	fd_in_funk(t_all *tmp)
{
	tmp->fd_in = open("./.ghost", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (tmp->fd_in != -1)
		add_fd(tmp, tmp->fd_in);
}

void	get_reverse_redirect(t_all *tmp, char **blok)
{
	char	*str;

	while (get_next_line(0, &str))
	{
		if ((ft_strncmp(str, *blok, ft_strlen(*blok)) == 0) \
			 && ft_strlen(*blok) == ft_strlen(str))
		{
			free(str);
			break ;
		}
		write(tmp->fd_in, str, ft_strlen(str));
		write(tmp->fd_in, "\n", 1);
		free(str);
	}
}
