/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:52 by abougy            #+#    #+#             */
/*   Updated: 2023/09/06 16:13:02 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	sig_check;

int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	t_signal	sig_act;
	int		i;

	i = -1;
	data.d_env = env;
	data.path = give_path(ft_getenv(env, "PATH"));
	pipe(data.fd);
	write(1, "launching...\n", 13);
	while (1)
	{
		if (signal(SIGINT, handle_signal) == SIG_ERR
				|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		{
			sigaction(SIGINT, &sig_act.ctrl_c, NULL);
			sigaction(SIGQUIT, &sig_act.ctrl_b, NULL);
		}
		if (!running(&data))
			break ;
	}
	while (data.path[++i])
		free(data.path[i]);
	free(data.path);
	return (0);
}
