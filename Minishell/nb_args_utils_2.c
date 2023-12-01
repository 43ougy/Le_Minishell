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
}

int	_print_error(void)
{
	write(2, "Cash'Hell: syntax error ", 24);
	write(2, "near unexpected token `|'\n", 26);
	return (1);
}

int	_check_pipe_error(char *input, int *i, t_prompt *data)
{
	int	tmp;

	data->input_len = 0;
	_set_pipe_data(data, &tmp, i);
	while (input[tmp] && input[tmp] != '|')
	{
		if (_is_alpha(input[tmp]))
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
		if (_add_args(data, data->prompt))
			return (1);
	}
	if (data->prompt[data->input_len] == '|')
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
