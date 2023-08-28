/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:52 by abougy            #+#    #+#             */
/*   Updated: 2023/08/28 10:43:49 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	execute(t_prompt *data)
{
	int		i;
	int		verif;

	i = -1;
	verif = 0;
	//FAIRE UN SPLIT SPECIALE POUR LES ARGUMENTS
	data->cmd = ft_split(data->prompt, ' ');
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
					exit(0);
				}
				else
					verif = 1;
			}
		}
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
		verif = 1;
	if (!verif)
		printf("%s: command not found\n", data->cmd[0]);
	i = -1;
	while (data->cmd[++i])
		free(data->cmd[i]);
	free(data->cmd);
}

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
	add_history(data->prompt);
	data->proc = fork();
	if (data->proc == -1)
		return (0);
	if (!data->proc)
	{
		execute(data);
	//	signal(SIGINT, SIG_DFL);
	}
	else
	{
		wait(NULL);
		//if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
		//	return (0);
		if (!data->prompt)
		{
			printf("\n");
			return (0);
		}
	}
}

char	**ft_getenv(char **env)
{
	int		li;
	int		ch;
	int		i;
	char	**split_path;
	char	*path;

	li = 0;
	i = 0;

	while (env[li])
	{
		ch = 0;
		while (env[li][ch] && env[li][ch] != '=')
			ch++;
		path = ft_substr(env[li], 0, ch);
		if (ft_strcomp("PATH", path))
		{
			path = env[li] + ch + 1;
			break ;
		}
		free(path);
		li++;
	}
	split_path = ft_split(path, ':');
	i = -1;
	while (split_path[++i])
		split_path[i] = ft_strjoin(split_path[i], "/");
	return (split_path);
}

int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	int		i;

	i = -1;
	data.d_env = env;
	data.path = ft_getenv(env);
	printf("launching...\n");
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		printf("failed to catch signal\n");
	while (1)
	{
		if (!running(&data))
			break ;
	}
	while (data.path[++i])
		free(data.path[i]);
	free(data.path);
	return (0);
}
