/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/09/16 16:11:25 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern	int	sig_check;

void	run_cd(t_prompt *data, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (i > 1)
		{
			write(1, "cd: too many arguments\n", 23);
			return ;
		}
	}
	if (!cmd[1])
	{
		if (chdir(ft_getenv(data->d_env, "HOME")) != 0)
			printf("%s is not a directory or doesn't exist\n", cmd[1]);
	}
	else if (chdir(cmd[1]) != 0)
		printf("%s is not a directory or doesn't exist\n", cmd[1]);
}

void	execute(t_prompt *data, int i)
{
	int	check;

	check = 0;
	if (execve(data->cmd[i][0], data->cmd[i], data->d_env) != -1)
		check = 1;
	else if (execve(ft_strjoin(data->cmd_path[i], data->cmd[i][0]), data->cmd[i], data->d_env) != -1)
		check = 1;
	else if (data->cmd_path[i])
	{
		if (ft_strcomp(data->cmd_path[i], "CD_CMD"))
		{
			run_cd(data, data->cmd[i]);
			check = 1;
		}
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt))
		exit_exec(data);
	if (!check)
		printf("%s: command not found\n", data->cmd[i][0]);
	exit_exec(data);
}

/*
void	execute(t_prompt *data)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	while (data->path[++i])
	{
		if (execve(data->cmd[0], data->cmd, data->d_env) != -1)
			verif = 1;
		else
		{
			//if (!builtin)
			//{
				if (execve(ft_strjoin(data->cmd_path[0], data->cmd[0]),
							data->cmd, data->d_env) == -1)
				{
					perror("Command 'execve' didn't work");
					exit_exec(data);
				}
				else
					verif = 1;
			//}
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
}*/

int	running(t_prompt *data)
{
	int	i;

	i = -1;
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
		data->cmd = parsing(data->prompt, data);
		data->proc = fork();
		if (data->proc == -1)
			return (0);
		if (!data->proc)
		{
			while (++i < data->nb_cmd)
				execute(data, i);
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
