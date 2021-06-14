#include "shell_truby.h"

int main(int ac, char **av)
{
	int i;

	i = execve("/usr/bin/bc", NULL, NULL);
	printf("%d\n", i);
}