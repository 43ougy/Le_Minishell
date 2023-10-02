#include "ra_shell.h"

extern int	g_sig_check;

void	execute(t_prompt *data, int i)
{
	int	check;

	if (data->cmd_path[i])
	{
		if (ft_strcomp(data->cmd_path[i], "CD_CMD"))
		{
			run_cd(data, data->cmd[i]);
			return ;
		}
	}
	check = 0;
	if (ft_strcomp(data->cmd_path[i], "CMD"))
		check = execve(data->cmd[i][0], data->cmd[i], data->d_env);
	else
		check = execve(ft_strjoin(data->cmd_path[i], data->cmd[i][0]), \
			data->cmd[i], data->d_env);
	if (check == -1)
		perror("execve()");
}

int	_execution(t_prompt *data)
{
	int	p_fd;

	p_fd = dup(0);
	data->nb_pipe = 0;
	if (pipe(data->fd))
		return (0);
	data->proc = fork();
	if (data->proc == -1)
	{
		close(p_fd);
		exit_exec(data);
	}
	if (!data->proc)
	{
		if (data->nb_pipe)
		{
			_pipe(data, &p_fd);
			exit(0);
		}
		else
		{
			execute(data, 0);
			exit_exec(data);
		}
	}
	g_sig_check = 1;
	wait(&data->proc);
	g_sig_check = 0;
	if (!data->prompt)
	{
		write(1, "\n", 1);
		return (0);
	}
}
