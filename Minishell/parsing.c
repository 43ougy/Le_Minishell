/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:59:54 by abougy            #+#    #+#             */
/*   Updated: 2023/09/11 09:56:59 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	get_nb_args(char *input)
{
	int	i;
	int	ret;
	int	j;

	i = 0;
	ret = 0;
	while (input[i])
	{
		if (!is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])//39 = ' & 34 = "
		{
			ret++;
			while (!is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])
				i++;
		}
		while (is_white_space(input[i]) && input[i] != 39 && input[i] != 34 && input[i])
			i++;
		if (input[i] == 39 || input[i] == 34)
		{
			j = i;
			i++;
			if (input[j] == 39)
			{
				while (input[i] != 39 && input[i])
					i++;
			}
			else if (input[j] == 34)
			{
				while (input[i] != 34 && input[i])
					i++;
			}
			if (i - j > 1 && (input[i] == 34 || input[i] == 39))
				ret++;
			else if (input[i] != 34 && input[i] != 39)
			{
				write(1, "Bad argument value\n", 19);
				return (-1);
			}
			i++;
		}
	}
	return (ret);
}

char	**get_args(char **ret, char *input, int nb_args)//attribution des arguments dans un double tableau
{
	int		i;
	int		j;
	int		ch;
	int		ar;

	i = -1;
	ch = 0;
	j = 0;
	while (++i < nb_args)
	{
		ar = 0;
		if (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
		{
			while (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
			{
				ch++;
				ar++;
			}
			ret[i] = malloc(sizeof(char) * ar + 1);
			if (!ret)
				return (NULL);
			ret[i] = ft_strncpy(ret[i], input + ch - ar, ar);
			ret[i][ar] = '\0';
		}
		else if (input[ch] == 39 || input[ch] == 34)
		{
			j = ch;
			ch++;
			if (input[j] == 39)
			{
				while (input[ch] != 39 && input[ch])
				{
					ch++;
					ar++;
				}
			}
			else if (input[j] == 34)
			{
				while (input[ch] != 34 && input[ch])
				{
					ch++;
					ar++;
				}
			}
			ret[i] = malloc(sizeof(char) * ar + 1);
			if (!ret)
				return (NULL);
			ret[i] = ft_strncpy(ret[i], input + ch - ar, ar);
			ret[i][ar] = '\0';
			ch++;
		}
		if (!ret[i])
			return (NULL);
		while (is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
			ch++;
	}
	ret[i] = NULL;
	return (ret);
}

void	args_check(int *check, char **args)
{
	int	i;
	
	i = -1;
	while (args[++i])
	{
		if (ft_strcomp("|", args[i]))
			check[0] += 1;
		else if (ft_strcomp("<", args[i]))
		{
			if (args[i][1] == '<')
				check[2] += 1;
			else
				check[1] += 1;
		}
		else if (ft_strcomp(">", args[i]))
		{
			if (args[i][1] == '>')
				check[3] += 1;
			else
				check[4] += 1;
		}
		else if (ft_strcomp("$", args[i]))
			check[5] += 1;
	}
}

// Variable check[6] :
// 0 = |
// 1-4 = < << >> >
// 5 = $

int	access_check(char **args, int nb_pipe, t_prompt *data)
{
	int		i;
	int		j;
	int		check;
	char	*path_cmd;

	i = -1;
	check = 0;
	if (!nb_pipe)
	{
		data->cmd_path = malloc(sizeof(char *) * 2);
		data->cmd_path[1] = NULL;
		if (!access(args[0], F_OK | X_OK))
			return (1);
		else
		{
			while (data->path[++i])
			{
				path_cmd = ft_strjoin(data->path[i], args[0]);
				if (!access(path_cmd, F_OK | X_OK))
				{
					free(path_cmd);
					data->cmd_path[0] = data->path[i];
					return (1);
				}
				free(path_cmd);
			}
		}
	}
	i = 0;
	while (nb_pipe >= 0)
	{
		if (!access(args[i], F_OK | X_OK))
		{
			check = 1;;
		}
		else
		{
			j = -1;
			while (data->path[++j])
			{
				path_cmd = ft_strjoin(data->path[j], args[i]);
				if (!access(path_cmd, F_OK | X_OK))
				{
					check = 1;
					free(path_cmd);
					break ;
				}
				else
					check = 0;
				free(path_cmd);
			}
		}
		if (!check)
		{
			printf("%s: command not found\n", args[i]);
			return (0);
		}
		while (!ft_strcomp(args[i], "|") && nb_pipe)
			i++;
		i++;
		nb_pipe--;
	}
	if (!check)
		return (0);
	return (1);
}

char	**parsing(char *input, t_prompt *data)//check args from the stdin (data->prompt)
{
	int			nb_args;
	char		**args;
	int			check[6];
	int			i;

	args = NULL;
	i = -1;
	nb_args = get_nb_args(input);
	args = malloc(sizeof(char *) * (nb_args + 1));
	if (!args)
		return (NULL);
	args = get_args(args, input, nb_args);
	while (++i < 6)
		check[i] = 0;
	args_check(check, args);
	data->nb_pipe = check[0];
	if (!access_check(args, data->nb_pipe, data))
	{
		i = 0;
		while (args[i])
		{
			free(args[i]);
			i++;
		}
		free(args);
		return (NULL);
	}
	return (args);
}
/*
int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	char	**args = parsing("ls", env, &data);
	int		i = 0;
	(void)ac;
	(void)av;
	if (!args)
	{
		while (data.path[i])
		{
		//	printf("%s\n", args[i]);
			free(data.path[i]);
			i++;
		}
		free(data.path);
		return (0);
	}
	while (args[i])
	{
	//	printf("%s\n", args[i]);
		free(args[i]);
		i++;
	}
	free(args);
	i = 0;
	while (data.path[i])
	{
	//	printf("%s\n", args[i]);
		free(data.path[i]);
		i++;
	}
	free(data.path);
	return (0);
}*/
