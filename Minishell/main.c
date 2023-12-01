/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:52 by abougy            #+#    #+#             */
/*   Updated: 2023/11/23 13:12:05 by abougy           ###   ########.fr       */
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

void	_init_data(t_prompt *data)
{
	data->check_exit = 0;
	data->exit_status = ft_itoa(0);
	data->set_env = NULL;
	data->path = NULL;
	data->cmde = NULL;
}

void	_free_all(t_prompt *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->exit_status)
		free(data->exit_status);
	_free_args_nexit(data);
	_free_struct(data);
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;

	(void)ac;
	(void)av;
	_init_data(&data);
	if (_make_env(&data, env))
		return (1);
	write(1, "launching...\n", 13);
	while (1)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		if (!running(&data))
			break ;
	}
	_free_all(&data);
	return (0);
}
