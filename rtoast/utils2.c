#include "../shell.h"

void	ctrl_slash_cat(int i)
{
	write(1, "\e[1CQuit: 3\n", 13);
}

void	cntrl_c_cat(int i)
{
	write(1, "\e[1C\n", 6);
}
