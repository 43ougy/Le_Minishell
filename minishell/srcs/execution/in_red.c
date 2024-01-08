/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_red.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:04 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:19:07 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_heredoc(int fd, char *delimiter);
/* -----------------------------------------*/

static void	write_file_input(char *file, int fd, int bytes)
{
	char	buff[256];
	int		input;

	input = open(file, O_RDONLY);
	if (input == -1)
	{
		perror(file);
		return ;
	}
	while (bytes > 0)
	{
		bytes = read(input, buff, 256);
		buff[bytes] = 0;
		write(fd, buff, m_strlen(buff));
	}
	close(input);
}

static void	read_input(int fd)
{
	int		rd_bytes;
	char	buff[256];

	rd_bytes = read(0, buff, 255);
	buff[rd_bytes] = 0;
	while (rd_bytes > 0)
	{
		write(fd, buff, m_strlen(buff));
		rd_bytes = read(0, buff, 256);
		buff[rd_bytes] = 0;
	}
}

static void	write_in_pipe(int fd, t_red *red, int pipe_type)
{
	int	index;

	index = -1;
	if (pipe_type == 1 || pipe_type == 3)
		read_input(fd);
	while (red->input2 && red->input2[++index])
		_heredoc(fd, red->input2[index]);
	index = -1;
	while (red->input1 && red->input1[++index])
		write_file_input(red->input1[index], fd, 1);
}

int	in_red(t_red *red, int pipe_type)
{
	int		pipe_fd[2];
	pid_t	pipe_id;

	if (!(m_tablen(red->input1) + m_tablen(red->input2))
		&& (pipe_type != 1 || pipe_type != 3))
		return (0);
	if (pipe(pipe_fd) == -1)
		return (-1);
	pipe_id = fork();
	if (pipe_id == -1)
		return (-1);
	if (!pipe_id)
	{
		close(pipe_fd[0]);
		//why write on file ?
		//free red and all
		free_red(red);
		write_in_pipe(pipe_fd[1], red, pipe_type);
		close(pipe_fd[1]);
		exit(0);
	}
	else
		close(pipe_fd[1]);
	return (pipe_fd[0]);
}

//write on pipe
//if ... | or | ... pipe type 1 or 3
//	read stdin and write buff to fd[1]
//check if this is an heredoc <<
//and when < write file in pipe
