/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:20:14 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:20:25 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	*_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	size_max;

	size_max = -1;
	if (count == size_max && size == size_max)
		return (NULL);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	_bzero(tab, (size * count));
	return (tab);
}

void	*_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

void	_free(char *string)
{
	if (string)
		free(string);
}

void	_free_args(t_prompt *data, int status)
{
	int	i;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			_free_tab(data->cmde[i].cmd);
			_free(data->cmde[i].path);
		}
		free(data->cmde);
	}
	_free_tab(data->d_env);
	_free_tab(data->path);
	exit(status);
}

char	**_endtab_push(char **tab, char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	if (!to_add)
		return (tab);
	while (tab && tab[len])
		len++;
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	len = 0;
	while (tab && tab[len])
	{
		ret[len] = tab[len];
		if (!ret[len++])
			return (_free_tab(ret));
	}
	ret[len] = _strdup(to_add);
	if (!ret[len++])
		return (_free_tab(ret));
	ret[len] = NULL;
	if (tab)
		free(tab);
	return (ret);
}
