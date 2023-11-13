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

void	_chevron_file(t_prompt *data, int i, int j)
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
		_chevron_file(data, i);
	}
}
