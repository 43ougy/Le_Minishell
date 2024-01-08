/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:55:40 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 16:56:09 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	m_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (size == 0)
		return (m_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (m_strlen(src));
}

char	*m_strjoin(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len = m_strlen(s1) + m_strlen(s2);
	ret = malloc(sizeof(char) * len + 1);
	while (s1[++i] && s1[i])
		ret[i] = s1[i];
	while (s2[++j] && s2[j])
		ret[i++] = s2[j];
	ret[len] = 0;
	return (ret);
}

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
		path = m_substr(env[li], 0, ch);
		if (m_strcmp(path_name, path))
		{
			free(path);
			path = NULL;
			path = m_strdup(env[li] + ch + 1);
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

	split_path = m_split(path, ':');
	path_slash = NULL;
	i = -1;
	while (split_path[++i])
	{
		path_slash = m_strjoin(split_path[i], "/");
		free(split_path[i]);
		split_path[i] = m_strdup(path_slash);
		free(path_slash);
	}
	free(path);
	return (split_path);
}

char	*_get_path(char *cmd, char **env)
{
	char	**all_path;
	char	*tmp_path;
	char	*cmd_path;
	char	*duplicate_cmd;
	int		i;

	i = -1;
	all_path = _give_path(_getenv(env, "PATH"));
	while (all_path[++i])
	{
		tmp_path = m_strjoin(all_path[i], "/");
		cmd_path = m_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (!access(cmd_path, F_OK | X_OK))
		{
			m_freetab(all_path);
			return (cmd_path);
		}
		free(cmd_path);
	}
	m_freetab(all_path);
	duplicate_cmd = m_strdup(cmd);
	return (duplicate_cmd);
}
