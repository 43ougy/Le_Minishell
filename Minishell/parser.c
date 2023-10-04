#include "ra_shell.h"

int	_is_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39)
		return (1);
	return (0);
}

int	_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (0);
	return (1);
}

int	_quotes(char *input, int *i, int *len)
{
	int	j;

	j = *i;
	if (input[j] == 34)
	{
		(*i)++;
		while (input[*i] != 34 && input[*i])
			(*i)++;
	}
	else if (input[j] == 39)
	{
		(*i)++;
		while (input[*i] != 39 && input[*i])
			(*i)++;
	}
	if ((*i) - j > 1)
		(*len)++;
	if (input[*i] != 34 && input[*i] != 39)
	{
			write(1, "quotes are open\n", 16);
			return (1);
	}
	(*i)++;
	return (0);
}

int	_nb_args(t_prompt *data, char *input, int method)
{
	int	i;
	int	nb_args;
	int	tmp;

	i = 0;
	nb_args = 0;
	if (method)
	{
		while (input[i])
		{
			if (!_is_char(input[i]) && input[i] != ' ')
			{
				nb_args++;
				while (!_is_char(input[i])/* && input[i] != ' '*/ && input[i])
					i++;
			}
			while (input[i] == ' ' && !_is_char(input[i]))
				i++;
			while (_is_char(input[i]) && input[i] != 34 && input[i] != 39 && input[i])
			{
				if (input[i] == '|' && input[i + 1] == '|')
					return (1);
				else if (input[i] == '|')
				{
					tmp = i + 1;
					while (input[tmp] != '|')
					{
						if (!_is_char(input[tmp]) && input[tmp] != ' ')
						{
							tmp = 0;
							break ;
						}
						tmp++;
					}
					if (tmp)
						return (1);
				}
				i++;
			}
			if (input[i] == 34 || input[i] == 39)
				if (_quotes(input, &i, &nb_args))
					return (1);
		}
		if (_is_char(input[i - 1]))
			return (1);
		data->cmde = malloc(sizeof(t_cmd) * nb_args + 1);
		if (!data->cmde)
			return (1);
		data->nb_args = nb_args;
		i = -1;
		while (++i < nb_args)
		{
			data->cmde[i].cmd = NULL;
			data->cmde[i].path = NULL;
			data->cmde[i].n_inarg = 0;
			data->cmde[i].infile = 0;
			data->cmde[i].outfile = 0;
		}
	}
	else if (!method)
	{
		if (input[i] == 34 || input[i] == 39)
		{
			printf("tset\n");
			if (_quotes(input, &i, &nb_args))
				return (1);
			printf("%d\n", data->nb_inar);
		}
		else
		{
			while (input[i] && !_is_char(input[i]))
			{
				if (input[i] != ' ' && input[i] != 34 && input[i] != 39)
				{
					nb_args++;
					while (!_is_char(input[i]) && input[i] != ' ' && input[i])
						i++;
				}
				while (input[i] == ' ' && !_is_char(input[i]) && input[i] != 34 && input[i] != 39)
					i++;
				if (input[i] == 34 || input[i] == 39)
					if (_quotes(input, &i, &nb_args))
						return (1);
			}
		}
		data->nb_inar = nb_args;
	}
	return (0);
}

int	_give_properties(t_prompt *data, char *input)
{
	int		i;
	int		j;
	int		n;
	char	*path_cmd;

	j = 0;
	i = -1;
	while (++i < data->nb_args)
	{
		n = -1;
		while (input[j] && !_is_char(input[j]))
			j++;
		if (input[j] == '<' && &data->cmde[i + 1])
		{
			n = data->cmde[i + 1].n_inarg;
			while (--n >= 0)
			{
				if (open(data->cmde[i + 1].cmd[n], O_RDONLY) == -1)
					return (1);
				data->cmde[i + 1].infile = 1;
			}
		}
		else if (input[j] == '>' && &data->cmde[i + 1])
		{
			while (++n < data->cmde[i + 1].n_inarg)
			{
				if (open(data->cmde[i + 1].cmd[0], O_CREAT | O_RDWR | O_TRUNC, 0644) == -1)
					return (1);
				else if (open(data->cmde[i + 1].cmd[n], O_RDONLY) == -1 && n > 0)
					return (1);
				data->cmde[i + 1].outfile = 1;
			}
		}
		if (!data->cmde[i].infile && !data->cmde[i].outfile)
		{
			n = -1;
			if (!access(data->cmde[i].cmd[0], F_OK | X_OK))
				data->cmde[i].path = "CMD";
			else if (ft_strcomp(data->cmde[i].cmd[0], "cd") ||
						ft_strcomp(data->cmde[i].cmd[0], "export") ||
						ft_strcomp(data->cmde[i].cmd[0], "unset"))
				data->cmde[i].path = data->cmde[i].cmd[0];
			else
			{
				while (data->path[++n])
				{
					path_cmd = ft_strjoin(data->path[n], data->cmde[i].cmd[0]);
					if (!access(path_cmd, F_OK | X_OK))
					{
						data->cmde[i].path = path_cmd;
						break ;
					}
					free(path_cmd);
				}
			}
		}
		while (input[j] && _is_char(input[j]) && input[j] != 34 && input[j] != 39)
			j++;
	}
	return (0);
}

int	_get_cmd(t_prompt *data, char *input)
{
	int	i;
	int	save;
	int	n;
	int	j;
	int	args;

	i = -1;
	save = 0;
	j = 0;
	while (++i < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_args(data, input + save, 0))
			return (1);
		data->cmde[i].n_inarg = data->nb_inar;
		data->cmde[i].cmd = malloc(sizeof(char *) * data->nb_inar);
		if (!data->cmde[i].cmd)
			return (1);
		args = -1;
		while (++args < data->nb_inar)
		{
			n = 0;
			if (input[j] == 34 || input[j] == 39)
			{
				if (input[j] == 34)
				{
					j++;
					while (input[j] != 34 && input[j])
					{
						j++;
						n++;
					}
				}
				if (input[j] == 39)
				{
					j++;
					while (input[j] != 39 && input[j])
					{
						j++;
						n++;
					}
				}
				data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
				if (!data->cmde[i].cmd[args])
					return (1);
				data->cmde[i].cmd[args] = ft_strncpy(data->cmde[i].cmd[args], input + save + 1, n);
				data->cmde[i].cmd[args][n] = '\0';
				j++;
				while ((!_is_whitespace(input[j]) || _is_char(input[j])) && input[j] != 34 && input[j] != 39)
					j++;
			}
			else
			{
				while (input[j] && input[j] == ' ')
					j++;
				while (input[j] && !_is_char(input[j]) && input[j] != ' ')
				{
					j++;
					n++;
				}
				data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
				if (!data->cmde[i].cmd[args])
					return (1);
				data->cmde[i].cmd[args] = ft_strncpy(data->cmde[i].cmd[args], input + save, n);
				data->cmde[i].cmd[args][n] = '\0';
				while ((!_is_whitespace(input[j]) || _is_char(input[j])) && input[j] != 34 && input[j] != 39)
					j++;
			}
			save = j;
		}
	}
	if (_give_properties(data, input))
		return (1);
	return (0);
}

void	_free_args(t_prompt *data)
{
	int	i;
	int	j;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			j = -1;
			if (data->cmde[i].cmd)
			{
				while (++j < data->cmde[i].n_inarg)
					free(data->cmde[i].cmd[j]);
				free(data->cmde[i].cmd);
			}
			if (data->cmde[i].path)
				free(data->cmde[i].path);
		}
		free(data->cmde);
	}
}

int	_parser(t_prompt *data)
{
	if (_nb_args(data, data->prompt, 1))
		return (1);
	if (_get_cmd(data, data->prompt))
		return (1);
	return (0); 
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	char *path = ft_getenv(env, "PATH");

	(void)ac;
	(void)av;
	data.path = give_path(path);
	free(path);
	data.nb_args = 0;
	data.nb_inar = 0;
	data.cmde = NULL;
	data.prompt = "cat < infile tsetfile testfile | wc -l | cat -e | husdfhi > outfile";
	_parser(&data);
	for (int i = 0; i < data.nb_args; i++)
	{
		printf("args %d :\n", i);
		for (int j = 0; j < data.cmde[i].n_inarg; j++)
		{
			printf("Infile = ");
			if (data.cmde[i].infile)
				printf("Yes\n");
			else
				printf("No\n");
			printf("Outfile = ");
			if (data.cmde[i].outfile)
				printf("Yes\n");
			else
				printf("No\n");
			printf("	%s\n", data.cmde[i].cmd[j]);
			if (data.cmde[i].path != NULL)
				printf("Path to [%s] is [%s]\n", data.cmde[i].cmd[0], data.cmde[i].path);
			else if (!data.cmde[i].path && !data.cmde[i].infile && !data.cmde[i].outfile)
				printf("Command: %s not found\n", data.cmde[i].cmd[0]);
			printf("\n");
		}
	}
	for (int i = 0; data.path[i]; i++)
		free(data.path[i]);
	free(data.path);
	_free_args(&data);
	return (0);
}
