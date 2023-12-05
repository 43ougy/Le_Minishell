#include "ra_shell.h"

size_t	_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
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

int	_atoi(char *str)
{
	long	nb;
	int		sig;

	nb = 0;
	sig = 1;
	if (*str == '-')
		sig = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!_is_num(*str))
			return (-1);
		nb = nb * 10 + (*str++ - '0');
	}
	if (nb * sig <= 0 || nb * sig > 2147483647)
		return (-1);
	return (nb);
}