#include "shell_truby.h"

void	exec(t_all *command, t_env *env)
{
	int i = -1;
	int j = -1;
	int res = -1;
	char *str = NULL;
	char *path = NULL;
	char **paths = NULL;

	while (ft_strnstr(env->str, "PATH=", 5) == NULL)
	{
		if (env->next == NULL)
			return ;						//error
		env = env->next;
	}
	str = ft_substr(env->str, 5, ft_strlen(env->str) - 5);
	paths = ft_split(str, ':');
	free(str);
	str = NULL;
	command->command_name = ft_strjoin_shell("/", command->command_name);
	while(res == -1 && paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], command->command_name);
		res = execve(path, &command->arg[1], NULL);
		if (res != -1)
		{
			free(path);
			path = NULL;
			while(paths[++j] != NULL)
			{
				free(paths[j]);
				paths[j] = NULL;
			}
			free(paths);
			break ;
		}
		free(path);
		path = NULL;
	}
}