/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:31:05 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:31:07 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	m_putstr(const char *str, int fd)
{
	write(fd, str, m_strlen(str));
}

int	m_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	**m_duplicatetab(char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		new_tab[i] = m_strdup(tab[i]);
		if (!new_tab[i])
			return (m_freetab(new_tab));
	}
	new_tab[i] = NULL;
	return (new_tab);
}

void	*m_freetab(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

char	*m_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = -1;
	if (!s)
		return (NULL);
	dest = malloc(sizeof(char) * (m_strlen(s) + 1));
	if (!dest)
		return (NULL);
	while (s[++i])
		dest[i] = s[i];
	dest[i] = 0;
	return (dest);
}
