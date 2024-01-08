/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:29:41 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:29:42 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_execute(t_parse *parse, t_shell *data, int fd_in, int *fd_out);
void	launch_pipe(int fd_in, int p_fd[2], t_parse *cmd, t_shell *data);
pid_t	g_proc;
/* ----------------------------------------- */

static void	_delete_file(char *file)
{
	if (access(file, F_OK) == -1)
		return ;
	unlink(file);
}

static int	launcher(t_parse *parse, t_shell *data)
{
	int		fd_in;
	int		*fd_out;
	int		status;

	fd_out = out_red(parse->red);
	for (int i = 0; fd_out[i] != -1; i++)
	{
		printf("fdout = %d\n", fd_out[i]);
	}
	if (!fd_out)
		return (1);
	fd_in = in_red(parse->red, parse->pipe_type);
	status = _execute(parse, data, fd_in, fd_out);
	write_to_file(fd_out);
	_delete_file(".tmp");
	free(fd_out);
	//free_red(parse->red);
	return (status);
}

static void	close_fd(int fd)
{
	if (fd > 2)
		close(fd);
}

void	execlist(t_shell *data)
{
	int		fd_in;
	int		p_fd[2];
	t_parse	*cmd;

	fd_in = 0;
	cmd = data->begin_list;
	if (!cmd->pipe_type)
	{
		printf("single command\n");
		data->ret_value = launcher(cmd, data);
	}
	else
	{
		while (cmd)
		{
			if (cmd->pipe_type == 3)
				p_fd[1] = 1;
			else if (pipe(p_fd) == -1)
				continue ;
			launch_pipe(fd_in, p_fd, cmd, data);
			close_fd(fd_in);
			fd_in = p_fd[0];
			cmd = cmd->next;
		}
	}
}

void	launch_pipe(int fd_in, int p_fd[2], t_parse *cmd, t_shell *data)
{
	pid_t	pid_pipe;

	pid_pipe = fork();
	if (pid_pipe == -1)
		return ;
	if (!pid_pipe)
	{
		if (p_fd[0] != fd_in)
			close_fd(p_fd[0]);
		dup2(fd_in, 0);
		dup2(p_fd[1], 1);
		launcher(cmd, data);
		close_fd(p_fd[1]);
		free_shell(data);
		exit(0);
	}
	close_fd(p_fd[1]);
	waitpid(pid_pipe, NULL, 0);
}
