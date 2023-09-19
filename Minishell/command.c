/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/09/19 15:25:36 by abougy           ###   ########.fr       */
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
			write(1, "Cash'Hell: cd: too many arguments\n", 34);
			return ;
		}
	}
	if (!cmd[1])
	{
		if (chdir(ft_getenv(data->d_env, "HOME")) != 0)
			perror("home");
	}
	else if (chdir(cmd[1]) != 0)
		perror(cmd[1]);
	execve("/usr/bin/ls", NULL, data->d_env);
}

void	execute(t_prompt *data, int i)
{
	int	check;

	if (i < data->nb_cmd - 1)
		dup2(data->fd[0], STDIN_FILENO);
	if (data->cmd_path[i])
	{
		if (ft_strcomp(data->cmd_path[i], "CD_CMD"))
		{
			run_cd(data, data->cmd[i]);
			dup2(data->fd[0], STDIN_FILENO);
			return ;
		}
	}
	check = 0;
	if (ft_strcomp(data->cmd_path[i], "CMD"))
		check = execve(data->cmd[i][0], data->cmd[i], data->d_env);
	else
		check = execve(ft_strjoin(data->cmd_path[i], data->cmd[i][0]), data->cmd[i], data->d_env);
	if (check == -1)
		perror("execve()");
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt))
		exit_exec(data);
}

int	running(t_prompt *data)
{
	int		i;
	//int		fd[2];

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
		if (!data->cmd)
			return (1);
		if (pipe(data->fd) == -1)
		{
			perror("pipe");
			exit_exec(data);
		}
		data->proc = fork();
		if (data->proc == -1)
			return (0);
		if (!data->proc)
		{
			i = -1;
			if (data->nb_cmd - 1 > 1)
			{
				while (++i < data->nb_cmd - 1)
				{
					execute(data, i);
					dup2(data->fd[1], STDOUT_FILENO);
					//close(data->fd[1]);
				}
			}
			else if (data->nb_cmd - 1 == 1);
				execute(data, i + 1);
			exit_exec(data);
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
