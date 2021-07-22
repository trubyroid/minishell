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
