/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:47 by abougy            #+#    #+#             */
/*   Updated: 2023/10/16 15:18:42 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

char	*ft_getenv(char **env, char *path_name)
{
	int		li;
	int		ch;
	char	*path;

	li = 0;
	path = NULL;
	while (env[li])
	{
		ch = 0;
		while (env[li][ch] && env[li][ch] != '=')
			ch++;
		path = ft_substr(env[li], 0, ch);
		if (ft_strcomp(path_name, path))
		{
			free(path);
			path = NULL;
			path = ft_strdup(env[li] + ch + 1);
			break ;
		}
		free(path);
		path = NULL;
		li++;
	}
	return (path);
}

char	**give_path(char *path)
{
	int		i;
	char	**split_path;
	char	*path_slash;

	split_path = ft_split(path, ':');
	path_slash = NULL;
	i = -1;
	while (split_path[++i])
	{
		path_slash = ft_strjoin(split_path[i], "/");
		free(split_path[i]);
		split_path[i] = path_slash;
	}
	return (split_path);
}
