/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_args_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:17:40 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:18:10 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_token_check_error(char *input, t_prompt *data)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (_is_char(input[i]))
	{
		if (input[i] == '|')
		{
			write(2, "Cash'Hell: syntax error ", 24);
			write(2, "near unexpected token `|'\n", 26);
		}
		else
		{
			write(2, "Cash'Hell: syntax error ", 24);
			write(2, "near unexpected token `newline'\n", 32);
		}
		if (data->exit_status)
			free(data->exit_status);
		data->exit_status = ft_strdup("2");
		return (1);
	}
	if (_is_limiter(input[i]) || (input[i] == '$' && !input[i + 1]))
	{
		write(1, &input[i], 1);
		write(1, ": command not found\n", 20);
		if (data->exit_status)
			free(data->exit_status);
		data->exit_status = ft_itoa(127);
		return (1);
	}
	return (0);
}

int	_check_chevron_error(char *input, int *j)
{
	int	i;

	i = 0;
	if (input[i] == '>' && input[i + 2] == '>')
	{
		write(2, "Cash'Hell: syntax error ", 24);
		write(2, "near unexpected token `>'\n", 26);
		return (1);
	}
	else
	{
		while (input[i] && input[i] == '>' && !_is_alpha(input[i]))
			i++;
		while (input[i] && input[i] == ' ' && !_is_alpha(input[i]))
			i++;
		if (!input[i])
		{
			write(2, "Cash'Hell: syntax error ", 24);
			write(2, "near unexpected token `newline'\n", 32);
			return (1);
		}
	}
	*j += i;
	return (0);
}

int	_check_rchevron_error(char *input, int *j)
{
	int	i;

	i = 0;
	if (input[i] == '<' && input[i + 2] == '<')
	{
		write(2, "Cash'Hell: syntax error ", 24);
		write(2, "near unexpected token `<'\n", 26);
		return (1);
	}
	else
	{
		while (input[i] && input[i] == '<' && !_is_alpha(input[i]))
			i++;
		while (input[i] && input[i] == ' ' && !_is_alpha(input[i]))
			i++;
		if (!input[i])
		{
			write(2, "Cash'Hell: syntax error ", 24);
			write(2, "near unexpected token `newline'\n", 32);
			return (1);
		}
	}
	*j += i;
	return (0);
}

void	_input_first_check(char *input, int *i, t_prompt *data)
{
	if (_is_alpha(input[*i]))
	{
		data->nb_args++;
		while (input[*i] && !_is_char(input[*i]) && !_is_quotes(input[*i]))
			(*i)++;
	}
	else if (input[*i] == '$' && input[*i + 1])
	{
		(*i)++;
		data->nb_args++;
		while (input[*i] && !_is_char(input[*i]) && !_is_quotes(input[*i]))
			(*i)++;
	}
	while (input[*i] && input[*i] == ' ' && !_is_char(input[*i])
		&& !_is_quotes(input[*i]))
		(*i)++;
}

void	_cmd_pipe_input(char *input, char *new_input, t_prompt *data)
{
	char	*cmd_pipe;
	int		i;
	int		j;

	i = -1;
	j = -1;
	cmd_pipe = malloc(sizeof(char) * (ft_strlen(new_input) + ft_strlen(input)));
	while (input[++i] && input[i])
		cmd_pipe[i] = input[i];
	while (new_input[++j] && new_input[j])
	{
		cmd_pipe[i] = new_input[j];
		i++;
	}
	cmd_pipe[i - 1] = '\0';
	free(data->prompt);
	data->prompt = ft_strdup(cmd_pipe);
	free(cmd_pipe);
	free(new_input);
}
