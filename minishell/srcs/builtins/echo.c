#include "execution.h"

static int	_check_option(t_prompt *data, int i, int *print_index)
{
	int	j;

	j = 0;
	if (ft_strcomp(data->cmde[i].cmd[1], "-n")
		&& ft_strcomp(data->cmde[i].cmd[1], "-n"))
	{
		while (ft_strcomp(data->cmde[i].cmd[++j], "-n"))
			(*print_index)++;
		return (1);
	}
	else if (data->cmde[i].cmd[1][0] == '-')
	{
		while (data->cmde[i].cmd[1][++j])
			if (data->cmde[i].cmd[1][j] != 'n')
				return (0);
		(*print_index)++;
		return (1);
	}
	return (0);
}

int	_echo(t_prompt *data, int i)
{
	int	option;
	int	print_index;

	option = 0;
	print_index = 0;
	option = _check_option(data, i, &print_index);
	while (data->cmde[i].cmd[++print_index])
	{
		write(1, data->cmde[i].cmd[print_index], \
			ft_strlen(data->cmde[i].cmd[print_index]));
		if (data->cmde[i].cmd[print_index + 1])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}