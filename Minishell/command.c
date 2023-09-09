/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/09/09 10:00:35 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern	int	sig_check;

void	run_cd(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
	{
		if (i > 1)
		{
			write(1, "cd: too many arguments\n", 23);
			return ;
		}
	}
	if (!data->cmd[1])
	{
		if (chdir(ft_getenv(data->d_env, "HOME")) != 0)
			printf("%s is not a directory or doesn't exist\n", data->cmd[1]);
		write(1, "tset2\n", 6);
	}
	else if (chdir(data->cmd[1]) != 0)
		printf("%s is not a directory or doesn't exist\n", data->cmd[1]);
}

void	execute(t_prompt *data)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	while (data->path[++i])
	{
		if (!access(data->cmd[0], F_OK | X_OK))
		{
			if (execve(data->cmd[0], data->cmd, data->d_env) != -1)
				verif = 1;
		}
		else
		{
			if (!access(ft_strjoin(data->path[i], data->cmd[0]), F_OK | X_OK))
			{
				if (execve(ft_strjoin(data->path[i], data->cmd[0]),
							data->cmd, data->d_env) == -1)
				{
					perror("Command 'execve' didn't work");
					exit_exec(data);
				}
				else
					verif = 1;
			}
		}
	}
	if (ft_strcomp("cd", data->cmd[0]))
	{
		write(1, "test\n", 5);
		run_cd(data);
		verif = 1;
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt))
		exit_exec(data);
	if (!verif)
		printf("%s: command not found\n", data->cmd[0]);
	exit_exec(data);
}

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		if (!(data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m")))
		{
			printf("\n");
			exit(0);
		}
	}
	if (data->prompt[0] == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
			exit(0);
		add_history(data->prompt);
		data->cmd = split_args(data->prompt);
		data->proc = fork();
		if (data->proc == -1)
			return (0);
		if (!data->proc)
		{
			execute(data);
		}
		else
		{
			sig_check = 1;
			wait(NULL);
			sig_check = 0;
			if (!data->prompt)
			{
				write(1, "\n", 1);
				return (0);
			}
		}
	}
	return (1);
}
