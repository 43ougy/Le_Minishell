/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:52 by abougy            #+#    #+#             */
/*   Updated: 2023/09/01 10:54:48 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	sig_check;

void	exit_exec(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->cmd[++i])
		free(data->cmd[i]);
	free(data->cmd);
	exit (0);
}

void	handle_signal(int signo)
{
	t_signal	sig_act;
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		if (!sig_check)
		{
		//	printf("--> %d, test", sig_check);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

char	*ft_getenv(char **env, char *path_name)
{
	int		li;
	int		ch;
	char	*path;

	li = 0;
	while (env[li])
	{
		ch = 0;
		while (env[li][ch] && env[li][ch] != '=')
			ch++;
		path = ft_substr(env[li], 0, ch);
		if (ft_strcomp(path_name, path))
		{
			path = env[li] + ch + 1;
			break ;
		}
		free(path);
		li++;
	}
	return (path);
}

void	run_cd(t_prompt *data)
{
	if (!data->cmd[1])
	{
		if (chdir(ft_getenv(data->d_env, "HOME")) != 0)
			printf("%s is not a directory or doesn't exist", data->cmd[1]);
	}
	else if (chdir(data->cmd[1]) != 0)
		printf("%s is not a directory or doesn't exist", data->cmd[1]);
}

void	execute(t_prompt *data)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	while (data->path[++i])
	{
		if (!access(data->cmd[0], F_OK | X_OK))
		{
			if (execve(data->cmd[0], data->cmd, data->d_env) != -1)
				verif = 1;
		}
		else
		{
			if (!access(ft_strjoin(data->path[i], data->cmd[0]), F_OK | X_OK))
			{
				if (execve(ft_strjoin(data->path[i], data->cmd[0]),
							data->cmd, data->d_env) == -1)
				{
					perror("Command 'execve' didn't work");
					exit_exec(data);
				}
				else
					verif = 1;
			}
		}
	}
	if (ft_strcomp("cd", data->cmd[0]))
	{
		run_cd(data);
		verif = 1;
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt))
		exit_exec(data);
	if (!verif)
		printf("%s: command not found\n", data->cmd[0]);
	exit_exec(data);
}

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		if (!(data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m")))
		{
			printf("\n");
			exit(0);
		}
	}
	if (data->prompt[0] == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
			exit(0);
		add_history(data->prompt);
		data->cmd = split_args(data->prompt);
		data->proc = fork();
		if (data->proc == -1)
			return (0);
		if (!data->proc)
		{
		//	write(1, "test\n", 5);
			execute(data);
		}
		else
		{
			sig_check = 1;
			wait(NULL);
			sig_check = 0;
		//	write(1, "test2\n", 6);
			if (!data->prompt)
			{
				write(1, "\n", 1);
				return (0);
			}
		}
	}
	return (1);
}

char	**give_path(char *path)
{
	int		i;
	char	**split_path;

	i = 0;
	split_path = ft_split(path, ':');
	i = -1;
	while (split_path[++i])
		split_path[i] = ft_strjoin(split_path[i], "/");
	return (split_path);
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	t_signal	sig_act;
	int		i;

	i = -1;
	data.d_env = env;
	data.path = give_path(ft_getenv(env, "PATH"));
	pipe(data.fd);
	write(1, "launching...\n", 13);
	while (1)
	{
	if (signal(SIGINT, handle_signal) == SIG_ERR
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		sigaction(SIGINT, &sig_act.ctrl_c, NULL);
		sigaction(SIGQUIT, &sig_act.ctrl_b, NULL);
	}
		if (!running(&data))
			break ;
	}
	while (data.path[++i])
		free(data.path[i]);
	free(data.path);
	return (0);
}
