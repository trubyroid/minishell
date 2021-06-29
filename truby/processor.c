#include "shell_truby.h"

t_env		*processor(t_all *command, t_env *env, char *home)
{
	pid_t	p;

	// printf("%s\n", command->arg[1]);
	if (strcmp("env", command->command_name) == 0)
		print_env(env);
	else if (strcmp("echo", command->command_name) == 0)
		use_echo(command);
	else if (strcmp("pwd", command->command_name) == 0)				//валидность комманд без
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
			add_enviroment_variable(command, env);					//валидность создаваемой/изменяемой строки
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