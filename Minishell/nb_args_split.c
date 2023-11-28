/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_args_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:03:19 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:03:20 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_check_quotes_error(char *input, int *in, int check_char, t_prompt *data)
{
	int	i;

	i = *in;
	if (_quotes(input, &i, &data->nb_args))
		return (1);
	if (!check_char && data->nb_args > 1)
		data->nb_args -= 1;
	*in = i;
	while (input[*in] && !_is_char(input[*in]))
		(*in)++;
	while (input[*in] && (_is_char(input[*in]) || input[*in] == ' '))
		(*in)++;
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
			if (input[i] == '|' && input[i + 1] == '|')
				return (1);
			else if (input[i] == '>' && _check_chevron_error(input + i, &i))
				return (1);
			else if (input[i] == '<' && _check_rchevron_error(input + i, &i))
				return (1);
			else if (input[i] == '|' && _check_pipe_error(input, &i, data))
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

void	_no_quotes(char *input, int *i, t_prompt *data)
{
	while (input[*i] && !_is_char(input[*i]) && !_is_quotes(input[*i]))
	{
		if (input[*i] != ' ' && !_is_quotes(input[*i]))
		{
			data->nb_inar++;
			while (input[*i] && !_is_char(input[*i]) && input[*i] != ' '
				&& !_is_quotes(input[*i]))
				(*i)++;
		}
		while (input[*i] && input[*i] == ' ' && !_is_char(input[*i])
			&& !_is_quotes(input[*i]))
			(*i)++;
	}
}

int	_nb_cmd(char *input, t_prompt *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (_is_quotes(input[i]))
			if (_quotes(input, &i, &data->nb_inar))
				return (1);
		if (!_is_quotes(input[i]))
		{
			_no_quotes(input, &i, data);
			if (input[i] == 34 || input[i] == 39)
				if (_quotes(input, &i, &data->nb_inar))
					return (1);
			return (0);
		}
	}
	return (0);
}

int	_nb_args(t_prompt *data, char *input, int method)
{
	if (method)
	{
		if (_token_check_error(input, data))
			return (1);
		if (_input_check_error(input, data))
			return (1);
		printf("in nb_args\n");
		data->cmde = malloc(sizeof(t_cmd) * data->nb_args + 1);
		if (!data->cmde)
			return (1);
		_init_cmde(data);
	}
	else if (!method)
		if (_nb_cmd(input, data))
			return (1);
	return (0);
}
