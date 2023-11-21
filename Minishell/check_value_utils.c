/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:05:28 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:05:36 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_environement_data(t_prompt *data, int *i, char *input, int *j)
{
	data->d_var[*j] = _env_variable(data, input + *i + 1);
	if (data->d_var[*j])
		data->val_len += ft_strlen(data->d_var[*j]);
	(*i)++;
	while (input[*i] && _is_alpha(input[*i]))
		(*i)++;
	(*j)++;
}

void	_exit_status(t_prompt *data, int *i)
{
	int	ch;

	ch = -1;
	while (data->exit_status[++ch])
		data->val_len++;
	(*i) += 2;
}

void	_dollar_attribute(char *input, t_prompt *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->val_len = 0;
	while (input[i] && input[i] != ' ' && !_is_quotes(input[i]))
	{
		while (input[i] && (_is_alpha(input[i]) || _is_limiter(input[i])))
		{
			i++;
			data->val_len++;
		}
		if (input[i] == '$' && input[i + 1] && (_is_alpha(input[i + 1])
				|| input[i + 1] == '_'))
			_environement_data(data, &i, input, &j);
		if (input[i] == '$' && ((!_is_alpha(input[i + 1]) && input[i + 1])
				|| !input[i + 1]) && input[i + 1] != '?')
		{
			i++;
			data->val_len++;
		}
		if (input[i] == '$' && (input[i + 1] && input[i + 1] == '?'))
			_exit_status(data, &i);
	}
}

void	_first_step(t_prompt *data, int *i, int *in, char *input)
{
	while (*i < data->val_len && input[*in] != '$' && input[*in])
	{
		data->d_cmd[*i] = input[*in];
		(*i)++;
		(*in)++;
	}
}

void	_d_var_to_d_cmd(t_prompt *data, int *i, int j)
{
	int	ch;

	ch = -1;
	while (data->d_var[j] && data->d_var[j][++ch] && *i < data->val_len)
	{
		data->d_cmd[*i] = data->d_var[j][ch];
		(*i)++;
	}
}
