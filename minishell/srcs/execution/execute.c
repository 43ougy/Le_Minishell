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

#include "minishell.h"

extern pid_t	g_proc;

static int	is_builtin(char *cmd)
{
	if (m_strcmp(cmd, "cd"))
		return (1);
	else if (m_strcmp(cmd, "echo"))
		return (2);
	else if (m_strcmp(cmd, "pwd"))
		return (3);
	else if (m_strcmp(cmd, "export"))
		return (4);
	else if (m_strcmp(cmd, "unset"))
		return (5);
	else if (m_strcmp(cmd, "env"))
		return (6);
	else if (m_strcmp(cmd, "exit"))
		return (7);
	return (0);
}

static int	exec_builtin(t_parse *parse, t_shell *data, int builtin, int fd)
{
	if (builtin == 1)
		return (m_cd(data, parse->cmds));
	else if (builtin == 2)
		return (m_echo(parse->cmds));
	else if (builtin == 3)
		return (m_pwd());
	else if (builtin == 4)
		return (m_export(data, parse->list_size, parse->cmds, fd));
	else if (builtin == 5)
		return (m_unset(data, parse->list_size, parse->cmds));
	else if (builtin == 6)
		return (m_env(data->env));
	else if (builtin == 7)
		m_exit(parse);
	return (-1);
}

//kill current process if CTRL^C is pressed (wc for exemple)
static void	exit_cmd(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	kill(g_proc, SIGKILL);
}

static void	exec(t_parse *parse, t_shell *data, int builtin)
{
	char	*path;

	if (builtin)
		exec_builtin(parse, data, builtin, 0);
	else if (!access(parse->cmds[0], F_OK | X_OK))
	{
		if (execve(parse->cmds[0], parse->cmds, data->env) == -1)
			perror(parse->cmds[0]);
	}
	else
	{
		path = _get_path(parse->cmds[0], data->env);
		if (!path)
			perror(path);
		if (execve(path, parse->cmds, data->env) == -1)
			perror(path);
		/* here */
		free(path);
	}
}

int	_execute(t_parse *parse, t_shell *data, int fd_in, int *fd_out)
{
	int		builtin;
	int		status;
	int		ret;

	builtin = is_builtin(parse->cmds[0]);
	if (builtin == 4)
		return (exec_builtin(parse, data, builtin, fd_out[0]));
	g_proc = fork();
	if (!g_proc)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(fd_in, 0);
		dup2(fd_out[0], 1);
		exec(parse, data, builtin);
		free(fd_out);
		free(data->prompt);
		m_freetab(data->env);
		free_list(data->begin_list, 0);
		exit(127);
	}
	signal(SIGINT, &exit_cmd);
	waitpid(g_proc, &status, 0);
	if (!WIFEXITED(status))
		return (-1);
	ret = WEXITSTATUS(status);
	return (ret);
}
