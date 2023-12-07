/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:18:03 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:18:05 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	is_env(char *env, char *name)
{
	int	i;

	i = 0;
	while ((env[i] && name[i]) && (env[i] == name[i]))
		i++;
	if (env[i] && name[i])
		return (0);
	return (1);
}

static void	remove_env(t_prompt *data, int i)
{
	free(data->env[i]);
	while (data->d_env[i + 1])
	{
		data->d_env[idx] = data->d_env[i + 1];
		i++;
	}
	data->d_env[i] = NULL;
}

int	_unset(t_prompt *data, int nb_args, char **args)
{
	int	i;

	i = 0;
	if (nb_args != 2)
		return (1);
	while (data->d_env[i] && !is_env(data->d_env[i], args[1]))
		i++;
	if (!data->d_env[i])
		return (1);
	remove_env(data, i);
	return (0);
}
