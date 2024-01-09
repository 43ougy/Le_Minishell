/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:31:12 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:31:14 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	m_iswhitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

void	m_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}

char	*m_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = -1;
	if (!dest || !src)
		return (NULL);
	while (++i < n && src[i])
		dest[i] = src[i];
	dest[n] = 0;
	return (dest);
}

int	m_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	//if (i < n && s1[i] != s2[i])
	//	return (1);
	//if (s1[i])
	//	return (1);
	return (0);
}

int	m_strcmp(char *s1, char *s2)
{
	int	i;
	int	len;

	i = 0;
	if (m_strlen(s1) > m_strlen(s2))
		len = m_strlen(s1);
	else
		len = m_strlen(s2);
	while (i < len)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
