/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/10/11 10:21:14 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	execute(t_prompt *data, int i)
{
	int	check;

	if (data->cmde[i].path)
	{
		if (ft_strcomp(data->cmde[i].path, "cd"))
		{
			run_cd(data, data->cmde[i].cmd);
			return ;
		}
	}
	check = 0;
//	printf("path-->%s, cmd-->%s | %s\n", data->cmde[i].path, data->cmde[i].cmd[0], data->cmde[i].cmd[1]);
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

	//printf("test\n");
	tmpin = dup(0);
	tmpout = dup(1);
	i = -1;
	if (data->infile)
	{
	//	printf("test fdin\n");
		fdin = open(data->cmde[1].cmd[0], O_RDONLY);
	}
	else
		fdin = dup(tmpin);
//	printf("prewhile test\n");
	while (++i < data->nb_args)
	{
//		printf("while test\n");
		dup2(fdin, 0);
		close(fdin);
		if (i == data->nb_args - 1)
		{
			if (data->cmde[i].outfile)
				fdout = open(data->cmde[i].cmd[0], O_RDONLY);
			else
				fdout = dup(tmpout);
		}
		else
		{
			pipe(data->fd);
			fdout = data->fd[1];
			fdin = data->fd[0];
		}
		dup2(fdout, 1);
		close(fdout);
		data->proc = fork();
		if (!data->proc)
		{
			execute(data, i);
			_free_args(data);
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	g_sig_check = 1;
	wait(&data->proc);
	g_sig_check = 0;
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

/*
int	_execution(t_prompt *data)
{
	int	p_fd;

	p_fd = dup(0);
	if (pipe(data->fd))
		return (0);
	data->proc = fork();
	if (data->proc == -1)
	{
		close(p_fd);
		_free_args(data);
		//exit_exec(data);
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
			_free_args(data);
			//exit_exec(data);
		}
	}
	else
	{
		
	}
	g_sig_check = 1;
	wait(&data->proc);
	g_sig_check = 0;
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
}*/
