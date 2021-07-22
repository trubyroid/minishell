#include "../shell.h"

void	error(int i, char *str)
{
	g_status = i;
	printf("%s\n", str);
}
