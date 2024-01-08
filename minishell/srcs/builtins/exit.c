/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:17:37 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:17:38 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_exit(t_parse *parse)
{
	int	i;
	int	status;

	i = -1;
	write(1, "exit\n", 5);
	while (parse->cmds[1][++i])
	{
		if (m_isalpha(parse->cmds[1][i]))
		{
			write(1, "bash: exit: ", 12);
			write(1, parse->cmds[1], m_strlen(parse->cmds[1]));
			write(1, ": numeric argument required\n", 28);
			status = 2;
			break ;
		}
	}
	if (m_isnum(parse->cmds[1][0]))
		status = m_atoi(parse->cmds[1]);
	exit (status);
}
