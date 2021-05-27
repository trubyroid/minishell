#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *find_next_lines(char *previous, char **env)
{
	char *next;
	int i = -1;
	int j = 0;

	while (env[++i] != NULL)
	{
		if (env[i][0] > previous[0])
		{
			next = env[i];
			break;
		}
		else if (env[i][0] == previous[0])
		{
			while (env[i][j] && previous[j])
			{
				if (env[i][j] > previous[j])
					next = env[i];
				if (env[i][j] < previous[j])
					break;
				j++;
			}
			j = 0;
		}
	}
	i = -1;
	while (env[++i] != NULL)
	{
		if (env[i][0] > previous[0] && env[i][0] < next[0])
		{
			next = env[i];
			i = 0;
		}
		else if (env[i][0] == previous[0])
		{
			while (env[i][j] && previous[j])
			{
				if (env[i][j] > previous[j] && env[i][j] < next[j])
					break;
				if (env[i][j] < previous[j])
					next = env[i];
				j++;
			}
			j = 0;
		}		
	}
	return (next);
}

static char	**find_first_line(char **env)
{
	int i = 0;
	int j = 1;
	char **export;
	char *first;

	while (env[i] != NULL)
		i++;
	export = malloc(sizeof(char*) * (i + 1));
	i = -1;
	first = env[0];
	while (env[++i] != NULL)
	{
		if (env[i][0] < first[0])
		{
			first = env[i];
			i = -1;
		}
		else if (env[i][0] == first[0])
		{
			while (env[i][j] && first[j])
			{
				if (env[i][j] > first[j])
					break;
				if (env[i][j] < first[j])
				{
					first = env[i];
					break;
				}
				j++;
			}
			j = 0;
		}
	}
	printf("%s", first);
	printf("%s", srt(first, env));
	free(export);
	return (export);
}

int	main(int ac, char **av, char **env)
{
	int i = -1;
	char **export;

	export = find_first_line(env);
	// while (export[++i] != NULL)
	// {
	// 	write(1, export[i], strlen(export[i]));
	// 	write(1, "\n", 1);
	// }
	return (0);
}