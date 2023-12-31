/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:17:22 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:17:24 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_check_option(char **cmd, int *index)
{
	int	j;

	j = 0;
	if (m_strcmp(cmd[1], "-n")
		&& m_strcmp(cmd[1], "-n"))
	{
		while (m_strcmp(cmd[++j], "-n"))
			(*index)++;
		return (1);
	}
	else if (cmd[1][0] == '-')
	{
		while (cmd[1][++j])
			if (cmd[1][j] != 'n')
				return (0);
		(*index)++;
		return (1);
	}
	return (0);
}

int	m_echo(char **cmd)
{
	int	option;
	int	index;

	option = 0;
	index = 0;
	option = _check_option(cmd, &index);
	while (cmd[++index])
	{
		write(1, cmd[index], \
			m_strlen(cmd[index]));
		if (cmd[index + 1])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
