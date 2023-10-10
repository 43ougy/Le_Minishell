/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/10/10 14:18:47 by abougy           ###   ########.fr       */
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
}
