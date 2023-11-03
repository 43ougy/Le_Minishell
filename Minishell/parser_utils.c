/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:45 by abougy            #+#    #+#             */
/*   Updated: 2023/11/03 11:29:54 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_free_struct(t_prompt *data)
{
	int	i;

	i = -1;
	if (data->d_env)
	{
		while (data->d_env[++i])
			free(data->d_env[i]);
		free(data->d_env);
		data->d_env = NULL;
	}
	i = -1;
	if (data->path)
	{
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
		data->path = NULL;
	}
}

void	_free_args(t_prompt *data, int status)
{
	int	i;
	int	j;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			j = -1;
			if (data->cmde[i].cmd)
			{
				while (++j < data->cmde[i].n_inarg)
					free(data->cmde[i].cmd[j]);
				free(data->cmde[i].cmd);
			}
			if (data->cmde[i].path)
				free(data->cmde[i].path);
		}
		free(data->cmde);
	}
	data->cmde = NULL;
	_free_struct(data);
	exit(status);
}

void	_free_args_nexit(t_prompt *data)
{
	int	i;
	int	j;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			j = -1;
			if (data->cmde[i].cmd)
			{
				while (++j < data->cmde[i].n_inarg)
					free(data->cmde[i].cmd[j]);
				free(data->cmde[i].cmd);
			}
			if (data->cmde[i].path)
				free(data->cmde[i].path);
		}
		free(data->cmde);
	}
	data->cmde = NULL;
}
