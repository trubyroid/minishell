#include <stdio.h>

int main(int ac, char **av)
{
	int i = 0;

	if (ac > 1)
	{
		while (++i < ac - 1)
			printf("%s ", av[i]);
		printf("%s\n", av[i]);
	}
	else
		printf("\n");
}