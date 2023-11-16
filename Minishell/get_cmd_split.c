#include "ra_shell.h"

int	_space_checker(char *input)
{
	int	i;

	i = 0;
	while (input[j] && input[j] == ' ')
		j++;
	if (!input[j] || input[j] == ' ')
		return (1);
	return (0);
}

int	_nb_cmd_check(t_prompt *data, char *input, int save, int i)
{
	if (_nb_args(data, input + save, 0))
		return (1);
	data->cmde[i].n_inarg = data->nb_inar;
	data->cmde[i].cmd = malloc(sizeof(char *) * (data->nb_inar + 1));
	if (!data->cmde[i].cmd)
		return (1);
	data->cmde[i].cmd[data->nb_inar] = NULL;
}

int	_get_cmd(t_prompt *data, char *input)
{
	int	i;
	int	save;

	i = -1;
	save = 0;
	data->equals = 0;
	if (_space_checker(input))
		return (1);
	while (++i < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_cmd_check(data, input, save, i))
			return (1);
	}
}
