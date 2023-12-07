/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:18 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:19:20 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	open_file(int index, t_red *red)
{
	int		append;
	int		fd;
	char	*file;

	append = 0;
	if (index >= _tblen(red->output1))
	{
		file = red->output2[index - _tblen(red->output1)];
		append = 1;
	}
	else
		file = red->output1[index];
	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(file);
	return (fd);
}

static int	*init_fdout(t_red *red, int len, int *i)
{
	int	*ret;

	if (len > 1)
		(*i)++;
	ret = malloc(sizeof(int) * (len + 2));
	if (!ret)
		return (NULL);
	if (len > 1)
	{
		ret[(*i)++] = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ret[(*i) - 1] == -1)
		{
			free(ret);
			return (NULL);
		}
	}
	return (ret);
}

int	*_out_red(t_red *red)
{
	int	len;
	int	*ret;
	int	i;
	int	j;

	j = 0;
	len = _tblen(red->output1) + _tblen(red->output2) + 1;
	ret = init_fdout(red, len, &i);
	if (!ret)
		return (NULL);
	while (j < len - 1)
	{
		ret[i] = open_file(j++, red);
		if (ret[i] == -1)
			return (NULL);
		i++;
	}
	if (len == 1)
		ret[i++] = 1;
	ret[i++] = -1;
	return (ret);
}
