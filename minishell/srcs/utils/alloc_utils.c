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

void	_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
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