#include "shell_truby.h"

static int	ft_check(t_all *command)
{
	if (((strcmp("env", command->command_name) == 0) &&											//pwd ваще похер, а вот env c аргументами запаристый
	(command->arg[1] != NULL)))
	{
		write(1, "Too many arguments.\n", 20);
        return (0);							//error
    }
	if (((strcmp("cd", command->command_name) == 0) ||
	(strcmp("export", command->command_name) == 0)) &&		
	(command->arg[2] != NULL))
	{
        write(1, "Too many arguments.\n", 20);
        return (0);							//error
    }
	return (1);
}

t_env		*processor(t_all *command, t_env *env, char *home)
{
	pid_t	p;

	if (ft_check(command) == 0)
    	return (NULL);
	if (strcmp("env", command->command_name) == 0)
		print_env(env);
	else if (strcmp("echo", command->command_name) == 0)						//заменить все strcmp
		use_echo(command);											
	else if (strcmp("pwd", command->command_name) == 0)
		use_pwd(command);
	else if (strcmp("unset", command->command_name) == 0)
		env = delete_enviroment_variable(command, env);
	else if (strcmp("cd", command->command_name) == 0)
		use_cd(env, command->arg, home);
	else if (strcmp("exit", command->command_name) == 0)
		close_minishell(env, home);
	else if (strcmp("export", command->command_name) == 0)
	{
		if (command->arg[1] == NULL)
			print_export(env);
		else
			add_enviroment_variable(command, env);
	}
	else
	{
		p = fork();
		if (p < 0)
    	{
    	    fprintf(stderr, "fork Failed" );
    	    return (NULL);							//error
    	}
		else if (p == 0)
		{
			if (command->fd_out != 1)
			{
				close(1);
				dup2(command->fd_out, 1);
			}
			if (command->fd_in != 0)
			{
				close(0);
				dup2(command->fd_in, 0);
			}
			exec(command, env);									//shlvl zsh minishell bash
		}
		wait(NULL);
	}
	return (env);
}