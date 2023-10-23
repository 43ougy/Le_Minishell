/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:40 by abougy            #+#    #+#             */
/*   Updated: 2023/10/23 14:48:15 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	handle_signal(int signo)
{
	t_signal	sig_act;

	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		if (!g_sig_check)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}
