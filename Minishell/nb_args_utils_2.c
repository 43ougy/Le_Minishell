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

	data->quit_cmd_pipe = 1;
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

void	_set_pipe_data(t_prompt *data, int *tmp, int *i)
{
	*tmp = (*i) + 1;
	data->nb_pipe++;
	data->quit_cmd_pipe = 0;
}

int	_print_error(void)
{
	write(2, "Cash'Hell: syntax error ", 24);
	write(2, "near unexpected token `|'\n", 26);
	return (1);
}

int	_input_check_error_re_use(char *input, t_prompt *data)
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

int	_add_args(t_prompt *data, char *input)
{
	if (_input_check_error_re_use(input + data->input_len, data))
		return (1);
	return (0);
}

int	_check_pipe_error(char *input, int *i, t_prompt *data)
{
	int	tmp;

	data->input_len = 0;
	_set_pipe_data(data, &tmp, i);
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
	(*i)++;
	if (tmp)
	{
		data->input_len = ft_strlen(data->prompt);
		_cmd_pipe(data->prompt, data);
		input = NULL;
		input = data->prompt;
		if (_add_args(data, input))
			return (1);
	}
	
	if (data->prompt[*i] == '|')
		return (_print_error());
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
