/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:13:54 by abougy            #+#    #+#             */
/*   Updated: 2023/11/24 12:11:09 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_heredoc_check(t_prompt *data)
{
	char	*ret;
	char	*line;

	ret = NULL;
	while (1)
	{
		line = NULL;
		write(1, "> ", 2);
		line = get_line(0);
		if (!line && _when_no_line(data, ret))
			return (1);
		if (ft_strcompn(line, data->cmde[1].cmd[0], ft_strlen(line)))
		{
			if (_heredoc_command(data, ret))
				return (1);
			free(line);
			free(ret);
			break ;
		}
		ret = ft_strjoin(ret, line);
		free(line);
	}
	data->heredoc = 0;
	return (0);
}

void	_child_process(t_prompt *data)
{
	if (!data->nb_pipe
		&& (ft_strcomp(data->cmde[0].path, "cd")
			|| ft_strcomp(data->cmde[0].path, "export")
			|| ft_strcomp(data->cmde[0].path, "unset")
		//	|| ft_strcomp(data->cmde[0].path, "env")
			|| ft_strcomp(data->cmde[0].path, "bad_set_env")
			|| ft_strcomp(data->cmde[0].path, "exit")
			|| ft_strcomp(data->cmde[0].path, "set_env")))
		exit(0);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execute(data, data->i);
	_free_args(data, 0);
}

void	_reset_redirect(t_prompt *data)
{
	dup2(data->tmpin, 0);
	dup2(data->tmpout, 1);
	close(data->tmpin);
	close(data->tmpout);
}

void	_exit_cmd(t_prompt *data, int status)
{
	int	i;

	i = -1;
	write(1, "exit\n", 5);
	while (data->cmde[0].cmd[1][++i])
	{
		if (_is_alpha(data->cmde[0].cmd[1][i]))
		{
			write(1, "bash: exit: ", 12);
			write(1, data->cmde[0].cmd[1],
				ft_strlen(data->cmde[0].cmd[1]));
			write(1, ": numeric argument required\n", 28);
			status = 2;
			break ;
		}
	}
	if (_is_num(data->cmde[0].cmd[1][0]))
		status = ft_atoi(data->cmde[0].cmd[1]);
	if (data->exit_status)
		free(data->exit_status);
	free(data->prompt);
	_free_args(data, status);
}

void	_cmd_execution(t_prompt *data, int status)
{
	if (ft_strcomp(data->cmde[0].path, "cd"))
		run_cd(data, data->cmde[0].cmd);
	if (ft_strcomp(data->cmde[0].path, "export"))
		data->d_env = run_export(data, data->cmde[0].cmd[1]);
	if (ft_strcomp(data->cmde[0].path, "unset"))
		data->d_env = run_unset(data, data->cmde[0].cmd[1]);
/*	if (ft_strcomp(data->cmde[0].path, "env"))
		run_env(data);*/
	if (ft_strcomp(data->cmde[0].path, "set_env"))
		data->set_env = run_set_equals(data, data->cmde[0].cmd[0]);
	if (ft_strcomp(data->cmde[0].path, "exit"))
		_exit_cmd(data, status);
}
