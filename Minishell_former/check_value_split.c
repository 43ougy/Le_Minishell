/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:02:04 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:02:10 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_init_d_var(t_prompt *data)
{
	data->d_var = malloc(sizeof(char *) * (data->dollar + 1));
	if (!data->d_var)
		return ;
	data->d_var[data->dollar] = NULL;
}

void	_free_d_var(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->d_var[++i])
		free(data->d_var[i]);
	free(data->d_var);
}

char	*_check_value(t_prompt *data, char *input)
{
	data->d_var = NULL;
	data->d_cmd = NULL;
	if (data->dollar)
	{
		_init_d_var(data);
		if (!data->d_var)
			return (NULL);
	}
	_dollar_attribute(input, data);
	data->d_cmd = malloc(sizeof(char) * data->val_len + 1);
	if (!data->d_cmd)
		return (NULL);
	data->d_cmd[data->val_len] = '\0';
	_command_attribute(input, data);
	if (data->dollar)
		_free_d_var(data);
	return (data->d_cmd);
}
