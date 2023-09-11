/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 08:25:14 by abougy            #+#    #+#             */
/*   Updated: 2023/09/11 09:06:27 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	size_t			i;
	char			*dest;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (i < ft_strlen(s))
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = -1;
	while (++i < n && src[i])
		dest[i] = src[i];
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
