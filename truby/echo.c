#include <stdio.h>

int main(int ac, char **av)
{
	int i = 0;

	while (++i < ac - 1)
		printf("%s ", av[i]);
	printf("%s", av[i]);
}