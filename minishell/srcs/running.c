#include "ra_shell.h"

/*static void	_path_running_check(t_prompt *data)
{
	char	*env_path;

	_free_tab(data->path);
	env_path = _getenv(data->d_env, "PATH");
	if (env_path)
	{
		data->path = _give_path(env_path);
		free(env_path);
	}
}*/

static int	first_prompt_check(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
		if (!data->prompt)
		{
			write(1, "exit\n", 5);
			//_free(data->exit_status);
			_free_tab(data->d_env);
			//_free_args(data, 0);
			exit (0);
		}
	}
	if (data->prompt[0] == '\0')
		return (1);
	else if (data->prompt[0] != '\0' && _strcomp("exit", data->prompt))
	{
		_free(data->prompt);
		//_free(data->exit_status);
		_free_tab(data->d_env);
		//_free_args(data, 0);
		exit (0);
	}
	return (0);
}

int	running(t_prompt *data)
{
	 if (first_prompt_check(data))
	 	return (0);
	 add_history(data->prompt);
	// if (data->check_exit > 0 && data->cmde)
	// 	_free_args_nexit(data);
	// _path_running_check(data);
	// data->check_exit = 1;
	// if (_parser(data))
	// 	return (0);
	// if (!data->cmde)
	// 	return (0);
	// if (!_execution(data))
	// 	return (1);
	_free(data->prompt);
	return (0);
}