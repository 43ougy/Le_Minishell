/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:49:06 by abougy            #+#    #+#             */
/*   Updated: 2023/09/11 09:04:20 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	ft_strcomp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcompn(char *s1, char *s2, int n)
{
	int	i;

	while(s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		i;
	int		j;

	i = -1;
	j = -1;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * len + 1);
	while (s1[++i] && s1[i])
		ret[i] = s1[i];
	while (s2[++j] && s2[j])
		ret[i++] = s2[j];
	ret[len] = 0;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	nlen;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	nlen = ft_strlen(s + start);
	if (nlen < len)
		len = nlen;
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s + start, len + 1);
	return (s2);
}
