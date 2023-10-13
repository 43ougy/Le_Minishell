/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:52 by abougy            #+#    #+#             */
/*   Updated: 2023/10/13 17:16:07 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	g_sig_check;

int	_make_env(t_prompt *data, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = 0;
	while (env[++i])
		len++;
	data->d_env = NULL;
	data->d_env = malloc(sizeof(char *) * (len + 1));
	if (!data->d_env)
		return (1);
	i = -1;
	while (env[++i])
		data->d_env[i] = ft_strdup(env[i]);
	data->d_env[len] = NULL;
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	t_signal	sig_act;
	int			i;

	i = -1;
	if (_make_env(&data, env))
		return (1);
	data.path = give_path(ft_getenv(data.d_env, "PATH"));
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
	i = -1;
	while (data.d_env[++i])
		free(data.d_env[i]);
	free(data.d_env);
	_free_args(&data);
	return (0);
}
