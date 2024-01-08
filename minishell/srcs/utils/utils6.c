/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 09:25:19 by abougy            #+#    #+#             */
/*   Updated: 2024/01/04 09:25:20 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*_free_buffer(char *buffer, char *buf)
{
	char	*temp;

	temp = m_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*cat_line(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	ret = m_calloc(sizeof(char), i + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] && line[i] == '\n')
		ret[i++] = '\n';
	free(line);
	return (ret);
}

static char	*read_stdin(int fd, char *line)
{
	char	*buff;
	int		bytes;

	if (!line)
		line = m_calloc(1, 1);
	buff = m_calloc(sizeof(char), 2);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, 1);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = 0;
		line = _free_buffer(line, buff);
		if (buff[0] == '\n')
			break ;
	}
	free(buff);
	return (line);
}

char	*m_getline(int fd)
{
	char	*line;

	line = m_calloc(1, 1);
	line = read_stdin(fd, line);
	if (!line)
		return (NULL);
	line = cat_line(line);
	if (!line)
		return (NULL);
	return (line);
}
