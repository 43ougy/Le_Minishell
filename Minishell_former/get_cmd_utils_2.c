/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:24:22 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:24:50 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_quotes_dollar_check(t_prompt *data, char *input, int quotes)
{
	data->i_check = data->index;
	data->index++;
	while (input[++data->i_check] && input[data->i_check] != quotes)
	{
		if (input[data->i_check] == '$' && input[data->i_check + 1]
			&& _is_alpha(input[data->i_check + 1]))
			data->dollar++;
		else if (input[data->i_check] == '$' && input[data->i_check + 1]
			&& input[data->i_check + 1] == '?')
			data->question_mark++;
	}
	if (quotes != 39 && (data->dollar > 0 || data->question_mark > 0))
	{
		if (_when_dollar(data, input, quotes))
			return (1);
	}
	else
	{
		while (input[data->index] != quotes && input[data->index])
		{
			data->index++;
			data->cmd_len++;
		}
	}
	return (0);
}

int	_when_quotes(t_prompt *data, char *input)
{
	if (input[data->index] == 34 && _quotes_dollar_check(data, input, 34))
		return (1);
	else if (input[data->index] == 39 && _quotes_dollar_check(data, input, 39))
		return (1);
	if (data->cmd_len)
	{
		data->cmde[data->args_count].cmd[data->cmd_count] = \
		malloc(sizeof(char) * data->cmd_len + 1);
		if (!data->cmde[data->args_count].cmd[data->cmd_count])
			return (1);
		data->cmde[data->args_count].cmd[data->cmd_count] = \
		ft_strncpy(data->cmde[data->args_count].cmd[data->cmd_count], \
		input + data->save_index + 1, data->cmd_len);
	}
	data->index++;
	while ((!_is_whitespace(input[data->index]) || _is_char(input[data->index]))
		&& !_is_quotes(input[data->index]) && input[data->index])
		data->index++;
	return (0);
}

void	_equals_check(t_prompt *data, char *input)
{
	data->i_check = data->save_index - 1;
	while (input[++data->i_check] && input[data->i_check] != ' ')
		if (input[data->i_check] == '=' && !data->dollar
			&& input[data->i_check - 1]
			&& _is_alpha(input[data->i_check - 1])
			&& input[data->i_check + 1]
			&& (_is_alpha(input[data->i_check + 1])
				|| input[data->i_check + 1] == '/'
				|| _is_num(input[data->i_check + 1])))
			data->equals++;
}

int	_cmd_init(t_prompt *data, char *input)
{
	while (input[data->index] && !_is_char(input[data->index])
		&& input[data->index] != ' ' && !_is_quotes(input[data->index]))
	{
		data->index++;
		data->cmd_len++;
	}
	data->cmde[data->args_count].cmd[data->cmd_count] = \
	malloc(sizeof(char) * data->cmd_len + 1);
	if (!data->cmde[data->args_count].cmd[data->cmd_count])
		return (1);
	data->cmde[data->args_count].cmd[data->cmd_count] = \
	ft_strncpy(data->cmde[data->args_count].cmd[data->cmd_count], \
	input + data->save_index, data->cmd_len);
	return (0);
}

int	_dollar_equals_check(t_prompt *data, char *input)
{
	if (_is_quotes(input[data->save_index]))
		return (0);
	data->i_check = data->save_index - 1;
	while (input[++data->i_check] && input[data->i_check] != ' ')
	{
		if (input[data->i_check] == '$' && input[data->i_check + 1]
			&& _is_alpha(input[data->i_check + 1]))
			data->dollar++;
		else if (input[data->i_check] == '$' && input[data->i_check + 1]
			&& input[data->i_check + 1] == '?')
			data->question_mark++;
	}
	_equals_check(data, input);
	if (data->dollar > 0 || data->question_mark > 0)
	{
		if (_when_dollar_no_quotes(data, input))
			return (1);
	}
	else if (_cmd_init(data, input))
		return (1);
	while (input[data->index] && (!_is_whitespace(input[data->index])
			|| _is_char(input[data->index]))
		&& !_is_quotes(input[data->index]))
		data->index++;
	return (0);
}
