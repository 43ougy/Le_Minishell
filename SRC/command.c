/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:25:34 by abougy            #+#    #+#             */
/*   Updated: 2023/07/13 08:43:55 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ra_shell.h"

int	verify_command(char *cmd, char *path)
{
	char	*path_name;
	path_name = ft_strjoin(path, cmd);
	if (!access(path_name, F_OK | X_OK))
		return (0);
	return (1);
}

void	run_command(char **path, char **env, char *p)
{
	char	**arg;
	int		j;
	int		verify;

	arg = ft_split(p, ' ');
	j = -1;
	verify = 0;
	if (ft_strcomp("cd", arg[0]))
	{
		if (chdir(arg[1]) != 0)
			printf("can't open, not a directory\n");
		free(arg);
		return ;
	}
	if (ft_strcomp("exit", p))
	{
		free(arg);
		exit(0);
	}
	while (path[++j])
		if (!verify_command(arg[0], path[j]))
			if (execve(ft_strjoin(path[j], arg[0]), arg, env) != -1)
				verify++;
	if (!verify)
		printf("Command '%s' not found\n", arg[0]);
	free(arg);
}

char	**get_env(void)
{
	int		j;
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	j = -1;
	while (path[++j])
		path[j] = ft_strjoin(path[j], "/");
	return (path);
}
