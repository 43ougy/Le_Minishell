/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:03:26 by abougy            #+#    #+#             */
/*   Updated: 2023/11/21 14:03:27 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_comp_name(t_prompt *data, t_run *run, char *name)
{
	int	len;
	int	i;

	i = -1;
	while (data->set_env[++i])
	{
		len = 0;
		while (data->set_env[i][len] && data->set_env[i][len] != '=')
			len++;
		run->comp = ft_substr(data->set_env[i], 0, len);
		if (ft_strcomp(name, run->comp))
		{
			free(run->comp);
			run->comp = ft_strdup(data->set_env[i]);
			run->i = -1;
			break ;
		}
		free(run->comp);
	}
}

void	_comp_env(t_prompt *data, t_run *run, char *name)
{
	int	i;
	int	len;

	i = -1;
	run->i = 0;
	while (data->d_env[++i])
	{
		len = 0;
		while (data->d_env[i][len] && data->d_env[i][len] != '=')
			len++;
		run->equal = ft_substr(data->d_env[i], 0, len);
		if (ft_strcomp(name, run->equal))
		{
			free(run->equal);
			free(data->d_env[i]);
			data->d_env[i] = ft_strdup(run->comp);
			free(run->comp);
			run->i = -1;
			break ;
		}
		free(run->equal);
	}
}

void	_env_len(t_prompt *data, t_run *run)
{
	run->len = 0;
	while (data->d_env[run->len])
		run->len++;
	run->len++;
}

char	**_set_export_env(t_prompt *data, t_run *run, char **new_env)
{
	int	i;

	i = -1;
	while (data->d_env[++i])
		new_env[i] = ft_strdup(data->d_env[i]);
	new_env[i] = ft_strdup(run->comp);
	new_env[run->len] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	data->d_env = NULL;
	free(run->comp);
	return (new_env);
}

char	**run_export(t_prompt *data, char *name)
{
	t_run	run;
	char	**new_env;

	new_env = NULL;
	run.i = 0;
	if (data->set_env)
	{
		_comp_name(data, &run, name);
		if (run.i != -1)
			return (data->d_env);
	}
	else
		return (data->d_env);
	if (data->d_env)
	{
		_comp_env(data, &run, name);
		if (run.i == -1)
			return (data->d_env);
	}
	_env_len(data, &run);
	new_env = malloc(sizeof(char *) * (run.len + 1));
	if (!new_env)
		return (NULL);
	new_env = _set_export_env(data, &run, new_env);
	return (new_env);
}
