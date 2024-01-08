/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:56:13 by abougy            #+#    #+#             */
/*   Updated: 2024/01/04 09:56:15 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	m_atoi(char *str)
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
		if (!m_isnum(*str))
			return (-1);
		nb = nb * 10 + (*str++ - '0');
	}
	if (nb * sig <= 0 || nb * sig > 2147483647)
		return (-1);
	return (nb);
}

int	m_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	m_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*m_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	nlen;

	if (!s)
		return (NULL);
	if (m_strlen(s) < (int)start)
		return (m_strdup(""));
	nlen = m_strlen(s + start);
	if (nlen < len)
		len = nlen;
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		return (NULL);
	m_strlcpy(s2, s + start, len + 1);
	return (s2);
}

void	*m_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	size_max;

	size_max = -1;
	if (count == size_max && size == size_max)
		return (NULL);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	m_bzero(tab, (size * count));
	return (tab);
}
