/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:12:46 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:13:49 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_infile_check(t_prompt *data)
{
	if (data->infile && !data->heredoc)
	{
		data->fdin = open(data->infile, O_RDONLY);
		if (data->fdin == -1)
		{
			write(1, "bash: ", 6);
			write(1, data->infile, ft_strlen(data->infile));
			write(1, ": No such file or directory\n", 28);
			return (1);
		}
	}
	else
		data->fdin = dup(data->tmpin);
	return (0);
}

void	_outfile_check(t_prompt *data)
{
	if (!data->append)
		data->fdout = open(data->outfile, O_RDWR | O_TRUNC);
	else
		data->fdout = open(data->outfile, O_RDWR | O_APPEND);
	if (data->fdout == -1)
		data->fdout = open(data->outfile, \
			O_CREAT | O_RDWR | O_TRUNC, 0644);
}

void	_fd_check_in_pipe(t_prompt *data)
{
	dup2(data->fdin, 0);
	close(data->fdin);
	if (data->i == data->nb_args - 1)
	{
		data->background = 0;
		data->fdout = dup(data->tmpout);
	}
	else if (data->i == data->nb_args - 2 && data->outfile)
		_outfile_check(data);
	else if (data->i == data->nb_args - 2 && data->infile)
		data->fdout = dup(data->tmpout);
	else
	{
		data->background = 1;
		pipe(data->fd);
		data->fdout = data->fd[1];
		data->fdin = data->fd[0];
	}
	dup2(data->fdout, 1);
	close(data->fdout);
}

int	_when_no_line(t_prompt *data, char *ret)
{
	write(1, "bash: warning: here-document delimited", 38);
	write(1, " by end-of-file (wanted `", 25);
	write(1, \
		data->cmde[1].cmd[0], ft_strlen(data->cmde[1].cmd[0]));
	write(1, "')\n", 3);
	if (ft_strcomp(data->cmde[0].cmd[0], "cat") && ret)
	{
		write(1, ret, ft_strlen(ret));
		data->exit_status = ft_itoa(0);
	}
	return (1);
}

int	_heredoc_command(t_prompt *data, char *ret)
{
	if (!ret)
		return (0);
	else if (ft_strcomp(data->cmde[0].cmd[0], "cat"))
	{
		write(1, ret, ft_strlen(ret));
		if (data->exit_status)
			free(data->exit_status);
		data->exit_status = ft_itoa(0);
		return (1);
	}
	else if (ft_strcomp(data->cmde[0].cmd[0], "echo"))
	{
		write(1, "\n", 1);
		if (data->exit_status)
			free(data->exit_status);
		data->exit_status = ft_itoa(0);
		return (1);
	}
	return (0);
}
