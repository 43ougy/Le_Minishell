#include "execution.h"

static int	_check_option(char *cmd, int *index)
{
	int	j;

	j = 0;
	if (_strcomp(cmd[1], "-n")
		&& _strcomp(cmd[1], "-n"))
	{
		while (_strcomp(cmd[++j], "-n"))
			(*index)++;
		return (1);
	}
	else if (cmd[1][0] == '-')
	{
		while (cmd[1][++j])
			if (cmd[1][j] != 'n')
				return (0);
		(*index)++;
		return (1);
	}
	return (0);
}

int	_echo(char *cmd)
{
	int	option;
	int	index;

	option = 0;
	index = 0;
	option = _check_option(cmd, &index);
	while (cmd[++index])
	{
		write(1, cmd[index], \
			_strlen(cmd[index]));
		if (cmd[index + 1])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}