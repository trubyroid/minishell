#include "shell.h"

int main(int argc, char **argv, char **env)
{
	t_all *tmp;
	char ss[10] = "  'cd'    ";
	int i = 0;

	tmp = (t_all*)malloc(sizeof(t_all));
	tmp->str = (char*)malloc(10 * sizeof(char*));
	tmp->str[9] = '\0';
	while (ss[i] != '\0')
	{
		tmp->str[i] = ss[i];
		i++;
	}
	prepars(tmp);
	start(tmp);
	printf("%s", tmp->command_name);
	free(tmp);
}
