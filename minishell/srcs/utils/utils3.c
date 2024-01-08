/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:31:18 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:31:20 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	reverse_tab(char *tab, int size)
{
	int		i;
	char	tmp;

	i = -1;
	while (++i < size / 2)
	{
		tmp = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = tmp;
	}
}

char	*m_itoa(int n)
{
	int			i;
	int			sign;
	char		buff[33];
	long int	nb;

	i = 0;
	sign = 0;
	nb = (long int)n;
	if (!n)
		return (m_strdup("0"));
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	while (nb)
	{
		buff[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (sign)
		buff[i++] = '-';
	buff[i] = 0;
	reverse_tab(buff, m_strlen(buff));
	return (m_strdup(buff));
}

static int	len_sep_string(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			counter++;
			while (s[i] && s[i] != c)
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
	while (s[*index + len] && s[*index + len] != c)
		len++;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len)
		ret[i++] = s[(*index)++];
	ret[i] = 0;
	return (ret);
}

char	**m_split(char const *s, char c)
{
	int		i;
	int		idx;
	int		len;
	char	**ret;

	i = 0;
	idx = 0;
	if (!s)
		return (NULL);
	len = len_sep_string(s, c);
	ret = malloc(len * sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < len - 1)
		ret[i++] = get_next_word(&idx, s, c);
	ret[i] = NULL;
	return (ret);
}
