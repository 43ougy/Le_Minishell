/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/10/13 17:46:06 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	run_env(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->d_env[++i])
	{
		write(1, data->d_env[i], ft_strlen(data->d_env[i]));
		write(1, "\n", 1);
	}
}

void	run_cd(t_prompt *data, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (i > 1)
		{
			write(2, "Cash'Hell: cd: too many arguments\n", 34);
			return ;
		}
	}
	if (!cmd[1])
	{
		if (chdir(ft_getenv(data->d_env, "HOME")) != 0)
			perror("home");
	}
	else if (chdir(cmd[1]) != 0)
		perror(cmd[1]);
}

char	**run_export(t_prompt *data, char *name)
{
	int		i;
	int		len;
	char	**new_env;

	i = -1;
	len = 1;
	new_env = NULL;
	while (data->d_env[++i])
		len++;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (data->d_env[++i])
		new_env[i] = ft_strdup(data->d_env[i]);
	new_env[i] = ft_strdup(name);
	new_env[len] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	return (new_env);
}
/*
void	run_unset(t_prompt *data, char *name)
{
}*/

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
		if (!data->prompt)
		{
			printf("exit\n");
			exit(0);
		}
	}
	if (data->prompt[0] == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return (1);
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
		exit(0);
	if (_parser(data))
		return (1);
	if (!data->cmde)
		return (1);
	add_history(data->prompt);
	if (!_execution(data))
		return (0);
	return (1);
}
