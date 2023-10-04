/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:07 by abougy            #+#    #+#             */
/*   Updated: 2023/10/04 15:46:08 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

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
