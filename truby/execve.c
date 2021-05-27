#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
	int i;

	i = execve("/usr/bin/bc", NULL, NULL);
	printf("%d\n", i);
}