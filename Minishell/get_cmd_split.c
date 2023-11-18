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

int	_quotes_dollar_check(t_prompt *data, char *input, int quotes)
{
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
	if (data->dollar > 0 || data->question_mark > 0)
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
	data->i_check = data->index;
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
		&& !_is_quotes(input[data->index]))
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
