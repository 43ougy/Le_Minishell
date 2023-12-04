/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _split.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 08:50:28 by abougy            #+#    #+#             */
/*   Updated: 2023/12/04 14:14:42 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

static int	len_sep_string(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			counter++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (counter + 1);
}

static char	*get_next_word(int *index, const char *s, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (s[*index] == c)
		(*index)++;
	while (s[*index + len] != c && s[*index + len])
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = s[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**_split(char const *s, char c)
{
	int		i;
	int		j;
	int		ac;
	char	**ret;

	i = 0;
	j = 0;
	ac = len_sep_string(s, c);
	ret = malloc(ac * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < ac - 1)
		ret[i++] = get_next_word(&j, s, c);
	ret[i] = NULL;
	return (ret);
}
