#include "ra_shell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;
	size_t	size_max;

	size_max = -1;
	if (count == size_max && size == size_max)
		return (NULL);
	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, (size * count));
	return (tab);
}

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*cat_line(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	ret = ft_calloc(sizeof(char), i + 2);
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

char	*read_stdin(int fd, char *line)
{
	char	*buff;
	int		bytes;

	if (!line)
		line = ft_calloc(1, 1);
	buff = ft_calloc(sizeof(char), 2);
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
		line = ft_free(line, buff);
		if (buff[0] == '\n')
			break ;
	}
	free(buff);
	return (line);
}

char	*get_line(int fd)
{
	char	*line;

	line = ft_calloc(1, 1);
	line = read_stdin(fd, line);
	if (!line)
		return (NULL);
	line = cat_line(line);
	if (!line)
		return (NULL);
	return (line);
}
