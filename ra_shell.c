/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:54:26 by abougy            #+#    #+#             */
/*   Updated: 2023/07/13 09:14:21 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ra_shell.h"

int	running(s_shell *data, char **env)
{
	if (isatty(0) && isatty(2))
		data->p = readline(data->prompt);
	else
		return (0);
	if (!data->p)
		return (0);
	add_history(data->p);
	data->pid = fork();
	if (data->pid == -1)
		return (0);
	if (!data->pid)
	{
		if (ft_strcomp("exit", data->p))
			exit (1);
		printf("enfant\n");
		run_command(data->path, env, data->p);
	}
	else if (data->pid)
	{
		if (ft_strcomp("exit", data->p))
			return (0);
		printf("parent\n");
		wait(NULL);
		kill(data->pid, SIGKILL);
	}
	return (1);
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	s_shell	data;
	int		i;

	(void)ac;
	(void)av;
	data.prompt = "Ra_shell$ ";
	data.path = get_env();
	while (1)
	{
		if (signal(SIGINT, handle_signal) == SIG_ERR)
			printf("failed to catch signal\n");
		if (!running(&data, env))
			break ;
	}
	i = -1;
	while (data.path[++i])
		free(data.path[i]);
	free(data.path);
	free(data.p);
	return (0);
}
