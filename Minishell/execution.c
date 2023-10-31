/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/10/31 09:54:35 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	execute(t_prompt *data, int i)
{
	int	check;

	if (ft_strcomp(data->cmde[i].path, "cd")
		|| ft_strcomp(data->cmde[i].path, "export")
		|| ft_strcomp(data->cmde[i].path, "unset")
		|| ft_strcomp(data->cmde[i].path, "bad_set_env")
		|| ft_strcomp(data->cmde[i].path, "set_env")
		|| ft_strcomp(data->cmde[i].path, "exit")
		|| ft_strcomp(data->cmde[i].path, "env"))
		return ;
	check = 0;
	if (ft_strcomp(data->cmde[i].path, "CMD"))
		check = execve(data->cmde[i].cmd[0], data->cmde[i].cmd, data->d_env);
	else
		check = execve(data->cmde[i].path, data->cmde[i].cmd, data->d_env);
	if (check == -1)
		perror("execve()");
}

int	_execution(t_prompt *data)
{
	int	tmpin;
	int	tmpout;
	int	fdin;
	int	fdout;
	int	i;
	int	status;

	tmpin = dup(0);
	tmpout = dup(1);
	i = -1;
	if (data->infile)
	{
		printf("FILE = [%s]\n", data->infile);
		fdin = open(data->infile, O_RDONLY);
		if (fdin == -1)
		{
			write(1, "bash: ", 6);
			write(1, data->infile, ft_strlen(data->infile));
			write(1, ": No such file or directory\n", 28);
		}
	}
	else
		fdin = dup(tmpin);
	while (++i < data->nb_args)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == data->nb_args - 1)
		{
			//printf("TEST|||||||\n");
			data->background = 0;
			fdout = dup(tmpout);
		}
		else if (i == data->nb_args - 2 && data->outfile)
		{
			if (!data->append)
				fdout = open(data->outfile, O_RDWR | O_TRUNC);
			else
				fdout = open(data->outfile, O_RDWR | O_APPEND);
			if (fdout == -1)
				fdout = open(data->outfile,
						O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		else if (i == data->nb_args - 2 && data->infile)
			fdout = dup(tmpout);
		else
		{
			data->background = 1;
			pipe(data->fd);
			fdout = data->fd[1];
			fdin = data->fd[0];
		}
		dup2(fdout, 1);
		close(fdout);
		data->proc = fork();
		if (!data->proc)
		{
			if (!data->nb_pipe
					&& (ft_strcomp(data->cmde[0].path, "cd")
					|| ft_strcomp(data->cmde[0].path, "export")
					|| ft_strcomp(data->cmde[0].path, "unset")
					|| ft_strcomp(data->cmde[0].path, "env")
					|| ft_strcomp(data->cmde[0].path, "bad_set_env")
					|| ft_strcomp(data->cmde[0].path, "exit")
					|| ft_strcomp(data->cmde[0].path, "set_env")))
			{
				printf("test\n");
				exit(0);
			}
			execute(data, i);
			_free_args(data);
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	g_sig_check = 2;
	if (!data->background)
		waitpid(data->proc, &status, 0);
	if (data->exit_status)
		free(data->exit_status);
	data->exit_status = ft_itoa(status);
	printf("STATUS = [%d]\n", status);
	g_sig_check = 0;
	if (!data->nb_pipe)
	{
		if (ft_strcomp(data->cmde[0].path, "cd"))
			run_cd(data, data->cmde[0].cmd);
		if (ft_strcomp(data->cmde[0].path, "export"))
			data->d_env = run_export(data, data->cmde[0].cmd[1]);
		if (ft_strcomp(data->cmde[0].path, "unset"))
			data->d_env = run_unset(data, data->cmde[0].cmd[1]);
		if (ft_strcomp(data->cmde[0].path, "env"))
			run_env(data);
		if (ft_strcomp(data->cmde[0].path, "set_env"))
			data->set_env = run_set_equals(data, data->cmde[0].cmd[0]);
		if (ft_strcomp(data->cmde[0].path, "exit"))
		{
			i = -1;
			write(1, "exit\n", 5);
			while (data->cmde[0].cmd[1][++i])
			{
				if (_is_alpha(data->cmde[0].cmd[1][i]))
				{
					write(1, "bash: exit: ", 12);
					write(1, data->cmde[0].cmd[1],
						ft_strlen(data->cmde[0].cmd[1]));
					write(1, ": numeric argument required\n", 28);
					break ;
				}
			}
			_free_args(data);
		}
	}
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}
