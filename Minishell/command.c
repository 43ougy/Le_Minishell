/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:00:33 by abougy            #+#    #+#             */
/*   Updated: 2023/10/20 15:52:01 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

extern int	g_sig_check;

void	run_env(t_prompt *data)
{
	int	i;

	i = -1;
	write(1, "MY ENV\n", 7);
	while (data->d_env[++i])
	{
		write(1, data->d_env[i], ft_strlen(data->d_env[i]));
		write(1, "\n", 1);
	}
}

void	run_cd(t_prompt *data, char **cmd)
{
	int		i;
	char	*home;

	i = -1;
	while (cmd[++i])
	{
		if (i > 1)
		{
			write(2, "Cash'Hell: cd: too many arguments\n", 34);
			return ;
		}
	}
	if (!cmd[1])
	{
		home = ft_getenv(data->d_env, "HOME");
		if (!home)
			write(2, "home doesn't exist\n", 19);
		if (chdir(home) != 0)
			perror("home");
		free(home);
	}
	else if (chdir(cmd[1]) != 0)
		perror(cmd[1]);
}

char	**run_export(t_prompt *data, char *name)
{
	int		i;
	int		len;
	char	**new_env;
	char	*comp;
	char	*equal;

	len = 0;
	new_env = NULL;
	i = -1;
	printf("Export test\n");
	if (data->set_env)
	{
		while (data->set_env[++i])
		{
			printf("SET_ENV in export = %s\n", data->set_env[i]);
			while (data->set_env[i][len] && data->set_env[i][len] != '=')
				len++;
			comp = ft_substr(data->set_env[i], 0, len);
			if (ft_strcomp(name, comp))
			{
				free(comp);
				comp = ft_strdup(data->set_env[i]);
				i = -1;
				break ;
			}
			free(comp);
		}
		if (i != -1)
			return (data->d_env);
	}
	else
		return (data->d_env);
	len = 0;
	while (data->d_env[len])
		len++;
	len++;
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (data->d_env[++i])
		new_env[i] = ft_strdup(data->d_env[i]);
	new_env[i] = ft_strdup(comp);
	new_env[len] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	data->d_env = NULL;
	free(comp);
	return (new_env);
}

char	**run_unset(t_prompt *data, char *name)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;
	char	*comp;

	i = -1;
	len = 0;
	j = 0;
	while (data->d_env[len])
	{
		while (data->d_env[len][j] && data->d_env[len][j] != '=')
			j++;
		comp = ft_substr(data->d_env[len], 0, j);
		if (ft_strcomp(name, comp))
		{
			free(comp);
			comp = ft_strdup(data->d_env[len]);
			break ;
		}
		free(comp);
		len++;
	}
	len = 0;
	while (data->d_env[len])
		len++;
	j = 0;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	while (data->d_env[++i])
	{
		if (data->d_env[i] && !ft_strcomp(data->d_env[i], comp))
			new_env[j] = ft_strdup(data->d_env[i]);
		j++;
	}
	new_env[len] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	free(comp);
	data->d_env = NULL;
	return (new_env);
}

char	**run_set_equals(t_prompt *data, char *input)
{
	char	**ret;
	int		i;
	int		j;
	int		len;

	len = 0;
	j = -1;
	ret = NULL;
	len = 0;
	if (data->set_env)
	{
		while (data->set_env[len])
		{
			if (ft_strcomp(data->set_env[len], input))
				return (data->set_env);
			len++;
		}
	}
	ret = malloc(sizeof(char *) * (len + 2));
	if (!ret)
		return (NULL);
	if (data->set_env)
	{
		while (++j < len + 2 && data->set_env[j])
		{
			ret[j] = ft_strdup(data->set_env[j]);
			free(data->set_env[j]);
		}
		free(data->set_env);
	}
	ret[len] = ft_strdup(input);
	ret[len + 1] = NULL;
	if (!ret)
		return (NULL);
	return (ret);
}

int	running(t_prompt *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[32mCash'Hell$ \x1B[0m");
		if (!data->prompt)
		{
			printf("exit\n");
			exit(0);
		}
	}
	if (data->prompt[0] == '\0')
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return (1);
	}
	if (data->prompt[0] != '\0' && ft_strcomp("exit", data->prompt) == 1)
		exit(0);
	if (data->check_exit > 0 && data->cmde)
		_free_args_nexit(data);
	data->check_exit = 1;
	if (_parser(data))
		return (1);
	if (!data->cmde)
		return (1);
	add_history(data->prompt);
	if (!_execution(data))
		return (0);
	return (1);
}
