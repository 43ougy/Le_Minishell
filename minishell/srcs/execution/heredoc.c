/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:17:20 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 16:17:22 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	_read_heredoc(int fd, char *delimiter, t_red *red)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = _get_line(0);
		if (!line)
			exit(1);
		if (_strcomp(line, delimiter))
			break ;
		write(fd, line, _strlen(line));
		free(line);
	}
	free(line);
	//free_all();
	exit(0);
}

static void	exit_heredoc(int sig)
{
	(void)sig;
	//kill current process if CTRL^C is pressed (wc for exemple)
	kill(data->proc_heredoc, SIGKILL);
}

void	_heredoc(int fd, char *delimiter, t_red *red)
{
	int		pipe_fd[2];
	int		bytes;
	char	buff[256];
	int		status;

	status = 0;
	bytes = 1;
	if (pipe(pipe_fd) == -1)
		return ;
	data->heredoc_proc = fork();
	if (!data->heredoc_proc)
		_read_heredoc(pipe_fd[1], delimiter, red);
	signal(SIGINT, &exit_heredoc);
	waitpid(data->proc_heredoc, &status, 0)
	close(pipe_fd[1]);
	while (!status && blytes > 0)
	{
		bytes = read(pipe_fd[0], buff, 256);
		buff[bytes] = 0;
		write(fd, buff, _strlen(buff));
	}
	close(pipe_fd[0]);
}
