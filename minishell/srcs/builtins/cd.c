/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:17:11 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:17:15 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	_cd(t_prompt *data, char **cmd)
{
	int		i;
	char	*home;

	i = -1;
	while (cmd[++i])
	{
		if (i > 1)
		{
			write(2, "Cash'Hell: cd: too many arguments\n", 34);
			return (1);
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
	return (0);
}
