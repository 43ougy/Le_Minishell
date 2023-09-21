/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/09/21 14:56:52 by abougy           ###   ########.fr       */
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

	if (data->cmd_path[i])
	{
		if (ft_strcomp(data->cmd_path[i], "CD_CMD"))
		{
			run_cd(data, data->cmd[i]);
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
}

int	exec_pipe(t_prompt *data, int i, int p_fd)
{
	int	fd[2];
	int	p_id;

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	p_id = fork();
	if (p_id == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(p_fd);
		return (-1);
	}
	else if (!p_id)
	{
		close(fd[0]);
		close(0);
		dup(p_fd);
		close(p_fd);
		if (!data->cmd[i++])
		{
			close(1);
			dup(fd[1]);
			close(fd[1]);
		}
		execute(data, i);
		exit_exec(data);
	}
	wait(&p_id);
	close(fd[1]);
	close(p_fd);
	return (fd[0]);
}

void	_pipe(t_prompt *data, int *p_fd)
{
	int	i;

	i = -1;
	while (++i < data->nb_cmd - 1)
		*p_fd = exec_pipe(data, i, *p_fd);
	close(*p_fd);
}

int	running(t_prompt *data)
{
	int	p_fd;
	int	i;
	int	j;

	p_fd = dup(0);
	data->nb_pipe = 0;
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
		data->cmd = parsing(data->prompt, data);
		if (!data->cmd)
			return (1);
		add_history(data->prompt);
		if (pipe(data->fd))
			return (0);
		data->proc = fork();
		if (data->proc == -1)
		{
			close(data->fd[0]);
			close(data->fd[1]);
			close(p_fd);
			exit_exec(data);
		}
		if (!data->proc)
		{
			if (data->nb_pipe)
			{
				_pipe(data, &p_fd);
				exit(0);
			}
			else
			{
				execute(data, 0);
				exit_exec(data);
			}
		}
		sig_check = 1;
		wait(&data->proc);
		sig_check = 0;
		if (!data->prompt)
		{
			write(1, "\n", 1);
			return (0);
		}
	}
	return (1);
}
