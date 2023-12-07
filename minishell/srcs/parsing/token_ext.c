/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:57 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:19:58 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

char	*add_str(char *src, char *str)
{
	int		i;
	char	*ret;

	i = -1;
	if (!src)
		return (_strdup(str));
	ret = _calloc(sizeof(char), _strlen(src) + _strlen(str) + 1);
	if (!ret)
		return (NULL);
	while (scr[++i])
		ret[i] = src[i];
	i = -1;
	while (str[++i])
		ret[_strlen(src) + i] = src[i];
	ret[_strlen(src) + _strlen(str)] = 0;
	free(src);
	return (ret);
}

char	*add_char(char *src, char c)
{
	char	*ret;
	int		len;
	int		i;

	i = -1;
	len = _strlen(src);
	ret = _calloc(sizeof(char), len + 2);
	if (!ret)
		return (NULL);
	while (scr[++i])
		ret[i] = src[i];
	ret[i] = c;
	ret[i + 1] = 0;
	free(src);
	return (ret);
}
