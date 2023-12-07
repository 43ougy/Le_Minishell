/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:18:37 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:26:44 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	exec_builtin(t_parse *parse, t_prompt *data, int builtin)
{
	if (builtin == 1)
		return (_cd(data, parse->cmd));
	else if (builtin == 2)
		return (_echo(parse->cmd));
	else if (builtin == 3)
		return (_pwd());
	else if (builtin == 4)
		return (_export(data, parse->list_size, parse->cmd));
	else if (builtin == 5)
		return (_unset(data, parse->list_size, parse->cmd));
	else if (builtin == 6)
		return (_env(data->d_env));
	else if (builtin == 7)
		_exit(parse);
}

static void	exit_cmd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	//kill current process if CTRL^C is pressed (wc for exemple)
	kill(data->proc, SIGKILL);
}

static void	_exec(t_parse *parse, t_prompt *data)
{
	char	*path;

	if (!access(parse->cmd[0], F_OK | X_OK))
	{
		if (execve(parse->cmd[0], parse->cmd, data->d_env) == -1)
			perror(parse->cmd[0]);
	}
	else
	{
		path = _get_path(parse->cmd[0], data->d_env);
		if (!path)
			perror(path);
		if (exeve(path, parse->cmd, data->d_env) == -1)
			perror(path);
		free(path);
	}
}

int	_execute(t_parse *parse, t_prompt *data, int fd_in, int fd_out)
{
	int		builtin;
	int		status; //maybe change it to data->status or smthg else
	pid_t	pid;

	builtin = is_builtin(parse->cmd[0]);
	if (builtin)
		return (exec_builtin(parse, builtin));
	data->proc = fork();
	if (!data->proc)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd_in, 0);
		dup2(fd_out, 1);
		exec(parse);
		exit(0);
	}
	signal(SIGINT, &exit_cmd);
	waitpid(data->proc, status, 0);
	if (!WIFEXITED(status))
		return (-1);
	return (WEXITSTATUS(status));
}
