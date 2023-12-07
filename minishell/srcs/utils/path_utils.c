/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:21:27 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:21:29 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

char	*_getenv(char **env, char *path_name)
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

char	**_give_path(char *path)
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
		split_path[i] = ft_strdup(path_slash);
		free(path_slash);
	}
	return (split_path);
}

char	*_get_path(char *cmd, char **env)
{
	char	**all_path;
	char	*tmp_path;
	char	*cmd_path;
	int		i;

	i = -1;
	all_path = _give_path(_get_env(env, "PATH"));
	while (all_path[++i])
	{
		tmp_path = _strjoin(all_path[i], "/");
		cmd_path = _strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free(cmd_path);
	}
	_free_tab(all_path);
	return (cmd);
}
