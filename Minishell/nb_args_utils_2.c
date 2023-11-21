/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_args_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:18:16 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:18:50 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_cmd_pipe(char *input, t_prompt *data)
{
	char	*new_input;

	write(1, "> ", 2);
	new_input = get_line(0);
	if (!new_input)
	{
		_free_struct(data);
		write(2, "Cash'Hell syntax error: unexpected end of file\n", 47);
		write(2, "exit\n", 5);
		if (data->exit_status)
			free(data->exit_status);
		data->exit_status = ft_strdup("2");
		exit(2);
	}
	if (!ft_strcomp(new_input, "\n"))
		_cmd_pipe_input(input, new_input, data);
}

int	_check_pipe_error(char *input, int *i, t_prompt *data)
{
	int	tmp;

	tmp = (*i) + 1;
	data->nb_pipe++;
	while (input[tmp] && input[tmp] != '|')
	{
		if (input[tmp] != ' ' && !_is_char(input[tmp])
			&& !_is_quotes(input[tmp]))
		{
			tmp = 0;
			break ;
		}
		tmp++;
	}
	if (tmp)
		_cmd_pipe(input, data);
	(*i)++;
	if (input[*i] == '|')
	{
		write(2, "Cash'Hell: syntax error ", 24);
		write(2, "near unexpected token `|'\n", 26);
		return (1);
	}
	return (0);
}

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
			if (_is_quotes(input[i])
				&& _check_quotes_error(input, &i, check_char, data))
				return (1);
		}
	}
	return (0);
}

void	_init_cmde(t_prompt *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_args)
	{
		data->cmde[i].cmd = NULL;
		data->cmde[i].path = NULL;
		data->cmde[i].n_inarg = 0;
		data->cmde[i].infile = 0;
		data->cmde[i].outfile = 0;
		data->cmde[i].file = 0;
	}
}
