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

#include "minishell.h"

static int	open_file(int index, t_red *red)
{
	int		append;
	int		fd;
	char	*file;

	append = 0;
	if (index >= m_tablen(red->output1))
	{
		file = red->output2[index - m_tablen(red->output1)];
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

static int	*init_fdout(int len, int *i)
{
	int	*ret;

	if (len > 1)
		len++;
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

int	*out_red(t_red *red)
{
	int	len;
	int	*ret;
	int	i;
	int	j;

	j = 0;
	i = 0;
	len = m_tablen(red->output1) + m_tablen(red->output2) + 1;
	ret = init_fdout(len, &i);
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

void	write_to_file(int *fdout)
{
	char	buff[256];
	int		bytes;
	int		fd;
	int		i;

	i = 0;
	while (fdout[++i] != -1)
	{
		fd = open(".tmp", O_RDONLY);
		if (fd == -1)
			continue ;
		bytes = read(fd, buff, 255);
		buff[bytes] = 0;
		while (bytes > 0)
		{
			write(fdout[i], buff, bytes);
			bytes = read(fd, buff, 255);
			buff[bytes] = 0;
		}
		if (fd > 2)
			close(fd);
	}
}
