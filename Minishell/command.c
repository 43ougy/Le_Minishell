/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/09/18 10:22:36 by abougy           ###   ########.fr       */
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

	if (data->cmd_path[i])
	{
		if (ft_strcomp(data->cmd_path[i], "CD_CMD"))
		{
			run_cd(data, data->cmd[i]);
			exit_exec(data);
		}
	}
	check = 0;
	check = execve(data->cmd[i][0], data->cmd[i], data->d_env);
	check = (execve(ft_strjoin(data->cmd_path[i], data->cmd[i][0]), data->cmd[i], data->d_env));
	if (check == -1);
		printf("Error: execve didn't work\n");
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt))
		exit_exec(data);
	exit_exec(data);
}

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
