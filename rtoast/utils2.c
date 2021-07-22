#include "../shell.h"

void	ctrl_slash_cat(int i)
{
	write(1, "\e[1CQuit: 3\n", 13);
}

void	cntrl_c_cat(int i)
{
	write(1, "\e[1C\n", 6);
}

void	signal_normal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_slash);
}

void	signal_cat(void)
{
	signal(SIGINT, cntrl_c_cat);
	signal(SIGQUIT, ctrl_slash_cat);
}

void	init_tmp(t_all *tmp)
{
	tmp->colnum_fd = 0;
	tmp->massiv_fd = NULL;
	tmp->baby_pipe = NULL;
	tmp->fd_out = 1;
	tmp->fd_in = 0;
	tmp->arg = NULL;
	tmp->num_arg = 0;
	tmp->command_name = NULL;
	tmp->file_name = NULL;
	tmp->redirect_i = 0;
}
