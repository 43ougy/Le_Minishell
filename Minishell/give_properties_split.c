#include "ra_shell.h"

void	_infile_chevron(t_prompt *data, int i)
{
	data->cmde[i + 1].infile = 1;
	data->infile = data->cmde[i + 1].cmd[0];
}

void	_outfile_chevron(t_prompt *data, int i)
{
	data->cmde[i + 1].outfile = 1;
	data->outfile = data->cmde[i + 1].cmd[0];
}

void	_chevron_file(t_prompt *data, int i, int j, char *input)
{
	int	n;

	n = -1;
	if (input[j] == '<' && input[j + 1] != '<')
		_infile_chevron(data, i);
	else if (input[j] == '<' && input[j + 1] == '<')
	{
		_infile_chevron(data, i);
		data->heredoc = 1;
	}
	else if (input[j] == '>' && input[j + 1] != '>')
		_infile_chevron(data, i);
	else if (input[j] == '>' && input[j + 1] == '>')
	{
		_infile_chevron(data, i);
		data->append = 1;
	}
	else
		while (++n < data->cmde[i].n_inarg)
			if (open(data->cmde[i].cmd[n], O_RDONLY) != -1)
				data->cmde[i].file = 1;
}

int	_no_path(t_prompt *data, int i)
{
	write(2, data->cmde[i].cmd[0], ft_strlen(data->cmde[i].cmd[0]));
	write(2, ": command not found\n", 20);
	if (data->exit_status)
		free(data->exit_status);
	data->exit_status = ft_strdup("127");
	return (1);
}

int	_path_test(t_prompt *data, int i)
{
	int		n;
	char	*path_cmd;

	n = -1;
	if (data->path)
	{
		while (data->path[++n])
		{
			path_cmd = ft_strjoin(data->path[n], data->cmde[i].cmd[0]);
			if (!access(path_cmd, F_OK | X_OK))
			{
				data->cmde[i].path = ft_strdup(path_cmd);
				free(path_cmd);
				break ;
			}
			free(path_cmd);
		}
	}
	if (!data->cmde[i].path)
		if (_no_path(data, i))
			return (1);
	return (0);
}

int	_command_path(t_prompt *data, int i)
{
	if (!access(data->cmde[i].cmd[0], F_OK | X_OK))
		data->cmde[i].path = "CMD";
	else if (ft_strcomp(data->cmde[i].cmd[0], "cd")
		|| ft_strcomp(data->cmde[i].cmd[0], "export")
		|| ft_strcomp(data->cmde[i].cmd[0], "unset")
		|| ft_strcomp(data->cmde[i].cmd[0], "exit")
		|| ft_strcomp(data->cmde[i].cmd[0], "env"))
		data->cmde[i].path = ft_strdup(data->cmde[i].cmd[0]);
	else if (data->equals > 0)
	{
		if (data->equals == 1 && !data->cmde[i].cmd[1])
			data->cmde[i].path = ft_strdup("set_env");
		else if ((data->equals == 1 && data->cmde[i].cmd[1])
			|| data->equals > 1)
			data->cmde[i].path = ft_strdup("bad_set_env");
	}
	else if (_path_test(data, i))
		return (1);
	return (0);
}

int	_give_properties(t_prompt *data, char *input)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	data->append = 0;
	data->heredoc = 0;
	if (ft_strcomp(data->cmde[0].cmd[0], " ") && !&data->cmde[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (++i < data->nb_args)
	{
		while (input[j] && !_is_char(input[j]) && !_is_quotes(input[j]))
			j++;
		_chevron_file(data, i, j, input);
		if (!data->cmde[i].infile && !data->cmde[i].outfile)
			if (_command_path(data, i))
				return (1);
		while (input[j] && _is_char(input[j]) && !_is_quotes(input[j]))
			j++;
	}
	return (0);
}
