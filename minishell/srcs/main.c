/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:29:12 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:29:13 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	running(t_shell *data);
/* ----------------------------------------- */

static void	init_data(t_shell *data, char *env[])
{
	data->env = m_duplicatetab(env);
	if (!data->env)
		exit (1);
	data->ret_value = 0;
	data->begin_list = NULL;
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	free_shell(t_shell *data)
{
	free(data->prompt);
	m_freetab(data->env);
	free_list(data->begin_list, 0);
}

int	main(int ac, char *av[], char *env[])
{
	t_shell	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (running(&data))
			break ;
	}
	free_shell(&data);
	return (0);
}
