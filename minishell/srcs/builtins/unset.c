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

#include "minishell.h"

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

static void	remove_env(t_shell *data, int i)
{
	free(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = data->env[i + 1];
		i++;
	}
	data->env[i] = NULL;
}

int	m_unset(t_shell *data, int nb_args, char **args)
{
	int	i;

	i = 0;
	if (nb_args != 2)
		return (1);
	while (data->env[i] && !is_env(data->env[i], args[1]))
		i++;
	if (!data->env[i])
		return (1);
	remove_env(data, i);
	return (0);
}
