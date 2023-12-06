#include "execution.h"

static int	is_builtin(char *cmd)
{
	if (_strcomp(cmd, "cd"))
		return (1);
	else if (_strcomp(cmd, "echo"))
		return (2);
	else if (_strcomp(cmd, "pwd"))
		return (3);
	else if (_strcomp(cmd, "export"))
		return (4);
	else if (_strcomp(cmd, "unset"))
		return (5);
	else if (_strcomp(cmd, "env"))
		return (6);
	else if (_strcomp(cmd, "exit"))
		return (7);
	return (0);
}

static int	exec_builtin(t_parse *parse, int builtin)
{
	if (builtin == 1)
		return (_cd());
	else if (builtin == 2)
		return (_echo());
	else if (builtin == 3)
		return (_pwd());
	else if (builtin == 4)
		return (_export());
	else if (builtin == 5)
		return (_unset());
	else if (builtin == 6)
		return (_env());
	else if (builtin == 7)
		_exit();
}

static void	exit_cmd(int sig)
{
	write(1, "\n", 1);
	//need to assign pid to something like g_var or struct
	//kill current process if CTRL^C is pressed (wc for exemple)
	kill(pid, SIGKILL);
}

void	_exec(t_parse *parse)
{
	char	*path;

	if (!access(parse->cmd[0], F_OK | X_OK))
	{
		if (execve(parse->cmd[0], parse->cmd, env) == -1)
			perror(parse->cmd[0])
	}
	else
	{
		path = _get_path(parse->cmd[0], env);
		if (!path)
			perror(path);
		if (exeve(path, parse->cmd, env) == -1)
			perror(path);
		free(path);
	}
}

int	_execute(t_parse *parse, int fd_in, int fd_out)
{
	int		builtin;
	int		status;
	pid_t	pid;

	builtin = is_builtin(parse->cmd[0])
	if (builtin)
		return (exec_builtin(parse, builtin))
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		exec(parse);
		exit(0);
	}
	signal(SIGINT, &exit_cmd);
	waitpid(pid, status, 0);
	if (!WIFEXITED(status))
		return(-1);
	return (WEXITSTATUS(status));
}