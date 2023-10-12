#include "ra_shell.h"

void	_one_method_one_split(char *input, int *i, int *nb_args)
{
	if (!_is_char(input[*i]) && input[*i] != ' '
		&& !_is_quotes(input[*i]))
	{
		(*nb_args)++;
		while (!_is_char(input[*i]) && input[*i]
			&& !_is_quotes(input[*i]))
			(*i)++;
	}
	while (input[*i] && input[*i] == ' ' && !_is_char(input[*i])
		&& !_is_quotes(input[*i]))
		(*i)++;
}

int	_two_method_one_split(t_prompt *data, int nb_args)
{
	int	i;

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
		data->cmde[i].file = 0;
	}
	return (0);
}

int	_three_method_one_split(t_prompt *data, char *input, int i)
{
	int	tmp;

	if (input[i] == '|' && input[i + 1] == '|')
		return (1);
	else if (input[i] == '|')
	{
		tmp = i + 1;
		data->nb_pipe++;
		while (input[tmp] != '|' && input[tmp])
		{
			if (!_is_char(input[tmp]) && input[tmp] != ' '
				&& !_is_quotes(input[tmp]))
			{
				tmp = 0;
				break ;
			}
			tmp++;
		}
		if (tmp)
		{
			write(2, "Error: no argument after pipe\n", 30);
			return (1);
		}
	}
	return (0);
}

int	_nb_args_method_one(t_prompt *data, char *input)
{
	int	i;
	int	check_char;
	int	nb_args;

	i = 0;
	nb_args = 0;
	check_char = 0;
	while (input[i])
	{
		_one_method_one_split(input, &i, &nb_args);
		while (_is_char(input[i]) && !_is_quotes(input[i]) && input[i])
		{
			check_char++;
			if (_three_method_one_split(data, input, i))
				return (1);
			i++;
		}
		if (_is_quotes(input[i]))
		{
			if (_quotes(input, &i, &nb_args))
				return (1);
			if (!check_char)
				nb_args -= 1;
			while (input[i] && !_is_char(input[i]))
				i++;
			while (input[i] && (_is_char(input[i]) || input[i] == ' '))
				i++;
		}
	}
	if (_is_char(input[i - 1]))
		return (1);
	if (_two_method_one_split(data, nb_args))
		return (1);
	return (0);
}
