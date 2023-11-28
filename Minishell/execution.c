/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/11/24 12:12:18 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

int	_check_cmd_exec(t_prompt *data, int i)
{
	if (ft_strcomp(data->cmde[i].path, "cd")
		|| ft_strcomp(data->cmde[i].path, "export")
		|| ft_strcomp(data->cmde[i].path, "unset")
		|| ft_strcomp(data->cmde[i].path, "bad_set_env")
		|| ft_strcomp(data->cmde[i].path, "set_env")
		|| ft_strcomp(data->cmde[i].path, "infile")
		|| ft_strcomp(data->cmde[i].path, "outfile")
		|| ft_strcomp(data->cmde[i].path, "exit"))
		return (1);
	if (ft_strcomp(data->cmde[i].path, "pwd")
		|| ft_strcomp(data->cmde[i].path, "echo")
		|| ft_strcomp(data->cmde[i].cmd[0], "clear")
		|| ft_strcomp(data->cmde[i].path, "env"))
	{
		if (ft_strcomp(data->cmde[i].path, "pwd"))
			run_pwd();
		if (ft_strcomp(data->cmde[i].path, "echo"))
			run_echo(data, i);
		if (ft_strcomp(data->cmde[i].path, "env"))
			run_env(data);
		if (ft_strcomp(data->cmde[i].cmd[0], "clear"))
			write(1, "\033c", 3);
		return (1);
	}
	return (0);
}

void	execute(t_prompt *data, int i)
{
	int	check;

	if (_check_cmd_exec(data, i))
		return ;
	check = 0;
	if (ft_strcomp(data->cmde[i].path, "CMD"))
		check = execve(data->cmde[i].cmd[0], data->cmde[i].cmd, data->d_env);
	else
		check = execve(data->cmde[i].path, data->cmde[i].cmd, data->d_env);
	if (check == -1)
		perror("execve()");
}
