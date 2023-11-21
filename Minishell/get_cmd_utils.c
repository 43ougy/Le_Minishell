/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:23:45 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:24:17 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_space_checker(t_prompt *data, char *input)
{
	while (input[data->index] && input[data->index] == ' ')
		data->index++;
	if (!input[data->index] || input[data->index] == ' ')
		return (1);
	return (0);
}

int	_nb_cmd_check(t_prompt *data, char *input)
{
	if (_nb_args(data, input + data->save_index, 0))
		return (1);
	data->cmde[data->args_count].n_inarg = data->nb_inar;
	data->cmde[data->args_count].cmd = \
	malloc(sizeof(char *) * (data->nb_inar + 1));
	if (!data->cmde[data->args_count].cmd)
		return (1);
	data->cmde[data->args_count].cmd[data->nb_inar] = NULL;
	return (0);
}

void	_set_data_value(t_prompt *data)
{
	data->save_index = 0;
	data->equals = 0;
	data->args_count = -1;
	data->index = 0;
}

int	_when_dollar(t_prompt *data, char *input, int quotes)
{
	data->cmde[data->args_count].cmd[data->cmd_count] = \
	_check_value(data, input + data->index);
	if (!data->cmde[data->args_count].cmd[data->cmd_count])
		return (1);
	while (input[data->index] && input[data->index] != quotes)
		data->index++;
	return (0);
}

int	_when_dollar_no_quotes(t_prompt *data, char *input)
{
	data->cmde[data->args_count].cmd[data->cmd_count] = \
	_check_value(data, input + data->index);
	if (!data->cmde[data->args_count].cmd[data->cmd_count])
		return (1);
	while (input[data->index] && input[data->index] != ' ')
		data->index++;
	return (0);
}
