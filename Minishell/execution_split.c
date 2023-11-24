/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:03:02 by abougy            #+#    #+#             */
/*   Updated: 2023/11/24 12:25:32 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

int	_set_status(t_prompt *data, int status)
{
	char	*give_status;

	if (WIFEXITED(status))
		data->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->status = 130;
		write(1, "\n", 1);
	}
	if (data->exit_status)
		free(data->exit_status);
	data->exit_status = NULL;
	give_status = ft_itoa(data->status);
	data->exit_status = ft_strdup(give_status);
	free(give_status);
	g_sig_check = 0;
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}

int	_execution(t_prompt *data)
{
	int	status;

	data->tmpin = dup(0);
	data->tmpout = dup(1);
	data->i = -1;
	if (_infile_check(data))
		return (1);
	while (++data->i < data->nb_args)
	{
		_fd_check_in_pipe(data);
		if (data->heredoc && _heredoc_check(data))
			return (1);
		data->proc = fork();
		if (!data->proc)
			_child_process(data);
	}
	_reset_redirect(data);
	g_sig_check = 2;
	if (!data->background)
		waitpid(data->proc, &status, 0);
	if (!data->nb_pipe)
		_cmd_execution(data, status);
	if (!_set_status(data, status))
		return (0);
	return (1);
}
