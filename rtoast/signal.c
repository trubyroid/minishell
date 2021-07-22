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
