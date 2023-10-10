/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:45 by abougy            #+#    #+#             */
/*   Updated: 2023/10/10 13:43:23 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_is_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (0);
	return (1);
}

void	_free_args(t_prompt *data)
{
	int	i;
	int	j;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			j = -1;
			if (data->cmde[i].cmd)
			{
				while (++j < data->cmde[i].n_inarg)
					free(data->cmde[i].cmd[j]);
				free(data->cmde[i].cmd);
			}
			if (data->cmde[i].path)
				free(data->cmde[i].path);
		}
		free(data->cmde);
	}
	exit(0);
}
