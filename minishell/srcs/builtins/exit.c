#include "execution.h"

void	_exit(t_prompt *data, int status)
{
	int	i;

	i = -1;
	write(1, "exit\n", 5);
	while (data->cmde[0].cmd[1][++i])
	{
		if (_is_alpha(data->cmde[0].cmd[1][i]))
		{
			write(1, "bash: exit: ", 12);
			write(1, data->cmde[0].cmd[1],
				ft_strlen(data->cmde[0].cmd[1]));
			write(1, ": numeric argument required\n", 28);
			status = 2;
			break ;
		}
	}
	if (_is_num(data->cmde[0].cmd[1][0]))
		status = ft_atoi(data->cmde[0].cmd[1]);
	_free(data->exit_status);
	_free(data->prompt);
	_free_tab(data);
	_free_args(data, status);
}