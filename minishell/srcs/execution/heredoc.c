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

#include "minishell.h"

char	*m_getline(int fd);
extern pid_t	g_proc;
/* --------------------------------------- */

static void	read_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = m_getline(0);
		if (!line)
			exit(1);
		if (m_strcmp(line, delimiter))
			break ;
		write(fd, line, m_strlen(line));
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
	kill(g_proc, SIGKILL);
}

void	_heredoc(int fd, char *delimiter)
{
	int		pipe_fd[2];
	int		bytes;
	char	buff[256];
	int		status;

	status = 0;
	bytes = 1;
	if (pipe(pipe_fd) == -1)
		return ;
	g_proc = fork();
	if (!g_proc)
		read_heredoc(pipe_fd[1], delimiter);
	signal(SIGINT, &exit_heredoc);
	waitpid(g_proc, &status, 0);
	close(pipe_fd[1]);
	while (!status && bytes > 0)
	{
		bytes = read(pipe_fd[0], buff, 256);
		buff[bytes] = 0;
		write(fd, buff, m_strlen(buff));
	}
	close(pipe_fd[0]);
}
