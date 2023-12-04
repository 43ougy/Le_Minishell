/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:49:06 by abougy            #+#    #+#             */
/*   Updated: 2023/12/04 14:10:44 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_strcomp(char *s1, char *s2)
{
	int	i;
	int	len;

	i = 0;
	if (_strlen(s1) > _strlen(s2))
		len = _strlen(s1);
	else
		len = _strlen(s2);
	while (i < len)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	_strcompn(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*_strjoin(char *s1, char *s2)
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
	len = _strlen(s1) + _strlen(s2);
	ret = malloc(sizeof(char) * len + 1);
	while (s1[++i] && s1[i])
		ret[i] = s1[i];
	while (s2[++j] && s2[j])
		ret[i++] = s2[j];
	ret[len] = 0;
	return (ret);
}

char	*_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	nlen;

	if (!s)
		return (NULL);
	if (_strlen(s) < start)
		return (_strdup(""));
	nlen = _strlen(s + start);
	if (nlen < len)
		len = nlen;
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		return (NULL);
	_strlcpy(s2, s + start, len + 1);
	return (s2);
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
