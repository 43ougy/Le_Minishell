#include "ra_shell.h"

int	_comp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

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

char	**_duplicate_tab(char **tab)
{
	int		i;
	int		len;
	char	**new_tab;

	i = -1;
	len = 0;
	while (tab[++i])
		len++;
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++i])
		new_tab[i] = _strdup(tab[i]);
	new_tab[len] = NULL;
	return (new_tab);
}

void	_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i]);
	free(tab);
}