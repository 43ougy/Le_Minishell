/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:47:12 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:47:14 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	m_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

char	**m_endtabpush(char **tab, const char *to_add)
{
	int		len;
	char	**ret;

	len = 0;
	if (!to_add)
		return (tab);
	ret = malloc(sizeof(char *) * (m_tablen(tab) + 2));
	if (!ret)
		return (NULL);
	while (tab && tab[len])
	{
		ret[len] = (char *)tab[len];
		if (!ret[len++])
			return (m_freetab(ret));
	}
	ret[len] = m_strdup(to_add);
	if (!ret[len++])
		return (m_freetab(ret));
	ret[len] = NULL;
	if (tab)
		free(tab);
	return (ret);
}
