/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/10/12 12:02:11 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	execute(t_prompt *data, int i)
{
	int	check;

	if (ft_strcomp(data->cmde[i].path, "cd"))
	{
		run_cd(data, data->cmde[i].cmd);
		return ;
	}
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

	tmpin = dup(0);
	tmpout = dup(1);
	i = -1;
	if (data->infile)
		fdin = open(data->cmde[1].cmd[0], O_RDONLY);
	else
		fdin = dup(tmpin);
	while (++i < data->nb_args)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == data->nb_args - 1)
		{
			data->background = 0;
			if (data->outfile)
			{
				fdout = open(data->outfile, O_RDWR);
				if (fdout == -1)
					fdout = open(data->outfile,
							O_CREAT | O_RDWR | O_TRUNC, 0644);
			}
			else
				fdout = dup(tmpout);
		}
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
			if (ft_strcomp(data->cmde[0].path, "cd") && !&data->cmde[1])
				exit(0);
			execute(data, i);
			_free_args(data);
		}
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	g_sig_check = 1;
	if (!data->background)
		waitpid(data->proc, NULL, 0);
	g_sig_check = 0;
	if (ft_strcomp(data->cmde[0].path, "cd") && !&data->cmde[1])
		run_cd(data, data->cmde[0].cmd);
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}
