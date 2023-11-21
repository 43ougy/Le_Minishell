/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:46:01 by abougy            #+#    #+#             */
/*   Updated: 2023/11/20 15:29:04 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	execute(t_prompt *data, int i)
{
	int	check;

	if (ft_strcomp(data->cmde[i].path, "cd")
		|| ft_strcomp(data->cmde[i].path, "export")
		|| ft_strcomp(data->cmde[i].path, "unset")
		|| ft_strcomp(data->cmde[i].path, "bad_set_env")
		|| ft_strcomp(data->cmde[i].path, "set_env")
		|| ft_strcomp(data->cmde[i].path, "exit")
		|| ft_strcomp(data->cmde[i].path, "env"))
		return ;
	if (ft_strcomp(data->cmde[i].cmd[0], "clear"))
	{
		write(1, "\033c", 3);
		return ;
	}
	check = 0;
	if (ft_strcomp(data->cmde[i].path, "CMD"))
		check = execve(data->cmde[i].cmd[0], data->cmde[i].cmd, data->d_env);
	else
		check = execve(data->cmde[i].path, data->cmde[i].cmd, data->d_env);
	if (check == -1)
		perror("execve()");
}
