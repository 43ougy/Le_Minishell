/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:22:33 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:22:35 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	g_sig_check;

void	handle_signal(int signo)
{
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

static void	_init_data(t_prompt *data)
{
	(void)data;
	// data->check_exit = 0;
	// data->exit_status = ft_itoa(0);
	// data->set_env = NULL;
	// data->path = NULL;
	// data->cmde = NULL;
}

static int	end_prog(t_prompt *data)
{
	_free(data->prompt);
	//_free(data->exit_status);
	//_free_args_nexit(data);
	_free_tab(data->d_env);
	_free_tab(data->path);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;

	(void)ac;
	(void)av;
	_init_data(&data);
	data.d_env = _duplicate_tab(env);
	if (!data.d_env)
		return (1);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (running(&data))
			break ;
	}
	return (end_prog(&data));
}
