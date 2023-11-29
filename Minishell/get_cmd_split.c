/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:03:46 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:03:49 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_set_data_value_while(t_prompt *data)
{
	data->cmd_len = 0;
	data->dollar = 0;
	data->question_mark = 0;
	data->save_index = data->index;
}

int	_get_cmd(t_prompt *data, char *input)
{
	_set_data_value(data);
	if (_space_checker(data, input))
		return (1);
	while (++data->args_count < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_cmd_check(data, input))
			return (1);
		data->cmd_count = -1;
		while (++data->cmd_count < data->nb_inar)
		{
			_set_data_value_while(data);
			if ((input[data->index] == 34 || input[data->index] == 39)
				&& _when_quotes(data, input))
				return (1);
			else if (_dollar_equals_check(data, input))
				return (1);
			data->save_index = data->index;
		}
	}
	if (_give_properties(data, input))
		return (1);
	return (0);
}
