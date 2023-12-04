/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/11/23 15:01:00 by abougy           ###   ########.fr       */
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
	int		i;
	char	*home;

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
		home = ft_getenv(data->d_env, "HOME");
		if (!home)
			write(2, "home doesn't exist\n", 19);
		if (chdir(home) != 0)
			perror("home");
		free(home);
	}
	else if (chdir(cmd[1]) != 0)
		perror(cmd[1]);
}

void	run_pwd(void)
{
	char	location[1024];

	if (!getcwd(location, sizeof(location)))
	{
		perror("pwd");
		return ;
	}
	write(1, location, ft_strlen(location));
	write(1, "\n", 1);
}

int	_check_option(t_prompt *data, int i, int *print_index)
{
	int	j;

	j = 0;
	if (ft_strcomp(data->cmde[i].cmd[1], "-n")
		&& ft_strcomp(data->cmde[i].cmd[1], "-n"))
	{
		while (ft_strcomp(data->cmde[i].cmd[++j], "-n"))
			(*print_index)++;
		return (1);
	}
	else if (data->cmde[i].cmd[1][0] == '-')
	{
		while (data->cmde[i].cmd[1][++j])
			if (data->cmde[i].cmd[1][j] != 'n')
				return (0);
		(*print_index)++;
		return (1);
	}
	return (0);
}

void	run_echo(t_prompt *data, int i)
{
	int	option;
	int	print_index;

	option = 0;
	print_index = 0;
	option = _check_option(data, i, &print_index);
	while (data->cmde[i].cmd[++print_index])
	{
		write(1, data->cmde[i].cmd[print_index], \
			ft_strlen(data->cmde[i].cmd[print_index]));
		if (data->cmde[i].cmd[print_index + 1])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
}
