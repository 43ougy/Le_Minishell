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

#include "execution.h"

void	_exit(t_parse *parse)
{
	int	i;
	int	status;

	i = -1;
	write(1, "exit\n", 5);
	while (parse->cmd[1][++i])
	{
		if (_is_alpha(parse->cmd[1][i]))
		{
			write(1, "bash: exit: ", 12);
			write(1, parse->cmd[1], _strlen(parse->cmd[1]));
			write(1, ": numeric argument required\n", 28);
			status = 2;
			break ;
		}
	}
	if (_is_num(parse->cmd[1][0]))
		status = _atoi(parse->cmd[1]);
}
