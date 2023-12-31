/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_args_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:17:33 by abougy            #+#    #+#             */
/*   Updated: 2023/11/30 08:17:36 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_check_input_error(t_prompt *data, char *input, int *i)
{
	if (input[*i] == '|' && input[*i + 1] == '|')
		return (1);
	else if (input[*i] == '>' && _check_chevron_error(input + *i, i))
		return (1);
	else if (input[*i] == '<' && _check_rchevron_error(input + *i, i))
		return (1);
	else if (input[*i] == '|' && _check_pipe_error(input, i, data))
		return (1);
	return (0);
}

int	_input_check_error(char *input, t_prompt *data)
{
	int	i;
	int	check_char;

	i = 0;
	check_char = 0;
	while (input[i])
	{
		_input_first_check(input, &i, data);
		while (input[i] && !_is_quotes(input[i]) && _is_char(input[i]))
		{
			check_char++;
			if (_check_input_error(data, input, &i))
				return (1);
			else if (data->quit_cmd_pipe)
				return (0);
		}
		if (_is_quotes(input[i])
			&& _check_quotes_error(input, &i, check_char, data))
			return (1);
	}
	return (0);
}

int	_add_args(t_prompt *data, char *input)
{
	if (_input_check_error(input + data->input_len, data))
		return (1);
	return (0);
}
