/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:37 by abougy            #+#    #+#             */
/*   Updated: 2023/11/16 18:17:19 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_quotes(char *input, int *i, int *len)
{
	int	j;

	j = *i;
	if (input[j] == 34)
	{
		(*i)++;
		while (input[*i] != 34 && input[*i])
			(*i)++;
	}
	else if (input[j] == 39)
	{
		(*i)++;
		while (input[*i] != 39 && input[*i])
			(*i)++;
	}
	if ((*i) - j > 1)
		(*len)++;
	if (input[*i] != 34 && input[*i] != 39)
	{
		write(2, "quotes are open\n", 16);
		return (1);
	}
	(*i)++;
	return (0);
}

char	*_env_variable(t_prompt *data, char *input)
{
	int		len;
	char	*env_var;
	char	*ret;
	int		i;

	len = 0;
	i = 0;
	while (input[i] && (_is_alpha(input[i]) || input[i] == '_'))
	{
		len++;
		i++;
	}
	env_var = malloc(sizeof(char) * len + 1);
	if (!env_var)
		return (NULL);
	env_var[len] = '\0';
	i = -1;
	while (++i < len)
		env_var[i] = input[i];
	ret = ft_getenv(data->d_env, env_var);
	free(env_var);
	if (!ret)
		return (NULL);
	return (ret);
}

int	_get_cmd(t_prompt *data, char *input)
{
	int	i;
	int	save;
	int	n;
	int	j;
	int	args;
	int	in;

	i = -1;
	save = 0;
	j = 0;
	data->equals = 0;
	/*while (input[j] && input[j] == ' ')
		j++;
	if (!input[j] || input[j] == ' ')
		return (1);
	while (++i < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_args(data, input + save, 0))
			return (1);
		data->cmde[i].n_inarg = data->nb_inar;
		data->cmde[i].cmd = malloc(sizeof(char *) * (data->nb_inar + 1));
		if (!data->cmde[i].cmd)
			return (1);
		data->cmde[i].cmd[data->nb_inar] = NULL;*/
		args = -1;
		while (++args < data->nb_inar)
		{
			n = 0;
			if (input[j] == 34 || input[j] == 39)
			{
				if (input[j] == 34)
				{
					save = j;
					j++;
					data->dollar = 0;
					in = j - 1;
					while (input[++in] && input[in] != 34)
						if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
							data->dollar++;
					if (data->dollar > 0)
					{
						data->cmde[i].cmd[args] = _check_value(data, input + j);
						if (!data->cmde[i].cmd[args])
							return (1);
						while (input[j] && input[j] != 34)
							j++;
					}
					else
					{
						while (input[j] != 34 && input[j])
						{
							j++;
							n++;
						}
					}
				}
				else if (input[j] == 39)
				{
					save = j;
					j++;
					data->dollar = 0;
					in = j - 1;
					while (input[++in] && input[in] != 39)
						if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
							data->dollar++;
					if (data->dollar > 0)
					{
						data->cmde[i].cmd[args] = _check_value(data, input + j);
						if (!data->cmde[i].cmd[args])
							return (1);
						while (input[j] && input[j] != 39)
							j++;
					}
					else
					{
						while (input[j] != 39 && input[j])
						{
							j++;
							n++;
						}
					}
				}
				if (n)
				{
					data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
					if (!data->cmde[i].cmd[args])
						return (1);
					data->cmde[i].cmd[args] = \
						ft_strncpy(data->cmde[i].cmd[args], input + save + 1, n);
				}
				j++;
				while ((!_is_whitespace(input[j]) || _is_char(input[j]))
					&& input[j] != 34 && input[j] != 39 && input[j])
					j++;
			}
			else
			{
				save = j;
				data->dollar = 0;
				data->question_mark = 0;
				in = save - 1;
				while (input[++in] && input[in] != ' ')
				{
					if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
						data->dollar++;
					else if (input[in] == '$' && input[in + 1]
							&& input[in + 1] == '?')
						data->question_mark++;
				}
				in = save - 1;
				while (input[++in] && input[in] != ' ')
					if (input[in] == '=' && !data->dollar && input[in - 1]
						&& _is_alpha(input[in - 1]) && input[in + 1]
						&& (_is_alpha(input[in + 1]) || input[in + 1] == '/'
							|| _is_num(input[in + 1])))
						data->equals++;
				if (data->dollar > 0)
				{
					data->cmde[i].cmd[args] = _check_value(data, input + j);
					if (!data->cmde[i].cmd[args])
						return (1);
					while (input[j] && input[j] != ' ')
						j++;
				}
				else
				{
					while (input[j] && !_is_char(input[j]) && input[j] != ' '
						&& input[j] != 34 && input[j] != 39)
					{
						j++;
						n++;
					}
					data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
					if (!data->cmde[i].cmd[args])
						return (1);
					data->cmde[i].cmd[args] = \
					ft_strncpy(data->cmde[i].cmd[args], input + save, n);
				}
				while (input[j] && (!_is_whitespace(input[j])
						|| _is_char(input[j]))
					&& input[j] != 34 && input[j] != 39)
					j++;
			}
			save = j;
		}
	}
	if (_give_properties(data, input))
		return (1);
	return (0);
}

int	_parser(t_prompt *data)
{
	data->nb_pipe = 0;
	data->nb_args = 0;
	data->infile = NULL;
	data->outfile = NULL;
	if (!data->prompt)
		return (1);
	if (_nb_args(data, data->prompt, 1))
		return (1);
	if (_get_cmd(data, data->prompt))
		return (1);
	return (0);
}
