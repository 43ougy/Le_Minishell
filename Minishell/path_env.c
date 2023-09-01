#include "ra_shell.h"

char	*ft_getenv(char **env, char *path_name)
{
	int		li;
	int		ch;
	char	*path;

	li = 0;
	while (env[li])
	{
		ch = 0;
		while (env[li][ch] && env[li][ch] != '=')
			ch++;
		path = ft_substr(env[li], 0, ch);
		if (ft_strcomp(path_name, path))
		{
			path = env[li] + ch + 1;
			break ;
		}
		free(path);
		li++;
	}
	return (path);
}

char	**give_path(char *path)
{
	int		i;
	char	**split_path;

	i = 0;
	split_path = ft_split(path, ':');
	i = -1;
	while (split_path[++i])
		split_path[i] = ft_strjoin(split_path[i], "/");
	return (split_path);
}
