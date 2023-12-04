/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:37 by abougy            #+#    #+#             */
/*   Updated: 2023/12/04 13:28:06 by nbeaufil         ###   ########.fr       */
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

int	_parser(t_prompt *data)
{
	data->nb_pipe = 0;
	data->nb_args = 0;
	data->infile = NULL;
	data->outfile = NULL;
	if (!data->prompt)
		return (1);
	if (_nb_args(data, data->prompt, 1))
	{
		free(data->prompt);
		return (1);
	}
	printf("nb_args -> %d\n", data->nb_args);
	fflush(stdout);
	if (_get_cmd(data, data->prompt))
	{
		free(data->prompt);
		return (1);
	}
	return (0);
}
