/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:40 by abougy            #+#    #+#             */
/*   Updated: 2023/09/09 10:00:42 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	sig_check;

void	exit_exec(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
		free(data->cmd[i]);
	free(data->cmd);
	exit (0);
}

void	handle_signal(int signo)
{
	t_signal	sig_act;
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		if (!sig_check)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
