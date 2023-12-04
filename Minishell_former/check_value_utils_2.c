/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:06:49 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:06:53 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_exit_status_to_d_cmd(t_prompt *data, int *i, int *in)
{
	int	ch;

	ch = -1;
	while (data->exit_status[++ch] && *i < data->val_len)
	{
		data->d_cmd[*i] = data->exit_status[ch];
		(*i)++;
	}
	(*in) += 2;
}

void	_dollar_set(t_prompt *data, int *i, int *in)
{
	data->d_cmd[*i] = '$';
	(*i)++;
	(*in)++;
}

void	_command_attribute(char *input, t_prompt *data)
{
	int	i;
	int	in;
	int	j;

	i = 0;
	in = 0;
	j = 0;
	while (i < data->val_len)
	{
		_first_step(data, &i, &in, input);
		if (input[in] == '$' && input[in + 1] && _is_alpha(input[in + 1]))
		{
			_d_var_to_d_cmd(data, &i, j);
			in++;
			while (input[in] && _is_alpha(input[in]))
				in++;
			j++;
		}
		if (input[in] == '$' && ((!_is_alpha(input[in + 1]) && input[in + 1])
				|| !input[in + 1]) && input[in + 1] != '?')
			_dollar_set(data, &i, &in);
		if (input[in] && input[in] == '$'
			&& (input[in + 1] && input[in + 1] == '?'))
			_exit_status_to_d_cmd(data, &i, &in);
	}
}
