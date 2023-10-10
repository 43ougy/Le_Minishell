/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/10/10 13:42:11 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	run_cd(t_prompt *data, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (i > 1)
		{
			write(1, "Cash'Hell: cd: too many arguments\n", 34);
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
	execve("/usr/bin/ls", NULL, data->d_env);
}

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
		if (!data->prompt)
		{
			printf("\n");
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
//	data->cmd = parsing(data->prompt, data);
	if (_parser(data))
		return (1);
	if (!data->cmde)
		return (1);
	add_history(data->prompt);
	if (!_execution(data))
		return (0);
	return (1);
}
