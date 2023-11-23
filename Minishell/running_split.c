/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:02:49 by abougy            #+#    #+#             */
/*   Updated: 2023/11/23 11:55:00 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_isatty_check(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
		if (!data->prompt)
		{
			write(1, "exit\n", 5);
			_free_struct(data);
			_free_args_nexit(data);
			if (data->exit_status)
				free(data->exit_status);
			exit(0);
		}
	}
}

int	_prompt_check(t_prompt *data)
{
	if (data->prompt[0] == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return (1);
	}
	return (0);
}

void	_exit_prompt_check(t_prompt *data)
{
	int	i;

	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
	{
		if (data->path)
		{
			i = -1;
			while (data->path[++i])
				free(data->path[i]);
			free(data->path);
		}
		if (data->prompt)
			free(data->prompt);
		if (data->exit_status)
			free(data->exit_status);
		exit(0);
	}
}

void	_path_running_check(t_prompt *data)
{
	char	*env_path;
	int		i;

	i = -1;
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	data->path = NULL;
	env_path = ft_getenv(data->d_env, "PATH");
	if (env_path)
	{
		data->path = give_path(env_path);
		free(env_path);
	}
}

int	running(t_prompt *data)
{
	_isatty_check(data);
	if (_prompt_check(data))
		return (1);
	_exit_prompt_check(data);
	add_history(data->prompt);
	if (data->check_exit > 0 && data->cmde)
		_free_args_nexit(data);
	_path_running_check(data);
	data->check_exit = 1;
	if (_parser(data))
		return (1);
	if (!data->cmde)
		return (1);
	if (!_execution(data))
		return (0);
	if (data->prompt)
		free(data->prompt);
	return (1);
}
