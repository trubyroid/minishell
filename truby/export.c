#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *find_next_line1(char *previous, char **env)
{
	
}

static char *find_next_line(char *previous, char **env)
{
	char *next;
	int i = -1;
	int j = 0;
	int	fl = 0;

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
				{
					next = env[i];
					break;
				}
				j++;
			}
			j = 0;
		}
	}
	i = -1;
	while (env[++i] != NULL)
	{
		// write(1, next, 15);
		// write(1, "\n", 1);
		if (env[i][0] > previous[0] && env[i][0] < next[0])
		{
			next = env[i];
		}
		else if (env[i][0] == previous[0])
		{
			if (env[i][0] != next[0])
			{
				while (env[i][j] && previous[j])
				{
					if (env[i][j] > previous[j])
					{
						next = env[i];
						fl = 1;
						break;
					}
					else if (env[i][j] < previous[j])
						break;
					j++;
				}
				j = 0;
			}
			else if (env[i][0] == next[0] && !fl)
			{
				// write(1, next, 15);
				// write(1, "\n", 1);
				while (env[i][j] && next[j])
				{
					if (env[i][j] > next[j]) //&& env[i][j] > previous[j])
					{
						next = env[i];
						break;
					}
					else if (env[i][j] < next[j])
						break;
					j++;
				}
				j = 0;
			}
			else if (env[i][0] == next[0] && fl)
			{
				// write(1, env[i], 15);
				// write(1, "ii", 2);
				// write(1, "\n", 1);
				while (env[i][j] && next[j])
				{
					if (env[i][j] < next[j] && env[i][j] > previous[j])
					{
						next = env[i];
						// fl = 0;
						break;
					}
					// else if (env[i][j] > next[j] && env[i][j] == previous[j])
					// {
					// 	next = env[i];
					// 	break;
					// }
					else if (env[i][j] > next[j])
						break;
					j++;
				}
				j = 0;
			}
		}
		else if (env[i][0] > previous[0] && env[i][0] == next[0])
		{
			while (env[i][j] && next[j])
			{
				if (env[i][j] < next[j])
				{
					next = env[i];
					break;
				}
				else if (env[i][j] > next[j])
					break;
				j++;
			}
			j = 0;
		}
		// else if (env[i][0] == previous[0] && env[i][0] != next[0])
		// {
		// 	while (env[i][j] && previous[j])
		// 	{
		// 		if (env[i][j] > previous[j])
		// 		{
		// 			next = env[i];
		// 			break;
		// 		}
		// 		else if (env[i][j] < previous[j])
		// 			break;
		// 		j++;
		// 	}
		// 	j = 0;
		// }
		// else if (env[i][0] == previous[0] && env[i][0] == next[0])
		// {
		// 	// write(1, env[i], 6);
		// 	// write(1, "\n", 1);
		// 	while (env[i][j] && next[j])
		// 	{
		// 		if (env[i][j] > previous[j])
		// 		{
		// 			if (env[i][j] < next[j])
		// 			{
		// 				next = env[i];
		// 				break;
		// 			}
		// 			else if (env[i][j] > next[j])
		// 			{

		// 			}
		// 			// write(1, next, 6);
		// 			// write(1, "\n", 1);
		// 		}
		// 		else if (env[i][j] > next[j] && env[i][j] != previous[j])
		// 			break;
		// 		j++;
		// 	}
		// 	j = 0;
			// write(1, next, 6);
			// write(1, "\n", 1);
		// }
		// else if (env[i][0] != previous[0] && env[i][0] == next[0])
		// {
			// write(1, next, 6);
			// write(1, "\n", 1);
			// while (env[i][j] && next[j])
			// {
			// 	if (env[i][j] < next[j] && env[i][j] != previous[j])
			// 	{
			// 		next = env[i];
					// write(1, next, 6);
					// write(1, "\n", 1);
					// break;
			// 	}
			// 	else if (env[i][j] > next[j])
			// 		break;
			// 	j++;
			// }
			// j = 0;
			// write(1, next, 6);
			// write(1, "\n", 1);
		// }
	}
	// write(1, next, 6);
	// write(1, "\n", 1);
	return (next);
}

static char	*find_first_line(char **env)
{
	int i = -1;
	int j = 1;
	char *first;

	first = env[0];
	while (env[++i] != NULL)
	{
		if (env[i][0] < first[0])
		{
			first = env[i];
			// i = -1;
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
	return (first);
}


int	main(int ac, char **av, char **env)
{
	int i = -1;
	char *line;

	// line = find_first_line(env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// line = find_next_line(line, env);
	// write(1, line, strlen(line));
	// write(1, "\n", 1);
	// while (line != NULL)
	// {
	// 	write(1, "\n", 1);
	// 	write(1, line, strlen(line));
	// 	line = find_next_line(line, env);
	// }
	return (0);
}