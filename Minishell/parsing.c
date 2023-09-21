/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:59:54 by abougy            #+#    #+#             */
/*   Updated: 2023/09/21 10:10:26 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	get_nb_args(char *input, int *i, t_prompt *data)
{
	int	ret;
	int	j;

	ret = 0;
	while (input[*i] && input[*i] != '|')
	{
		if (!is_white_space(input[*i]) && input[*i] != 39 && input[*i] != 34 && input[*i])//39 = ' & 34 = "
		{
			ret++;
			while (!is_white_space(input[*i]) && input[*i] != 39 && input[*i] != 34 && input[*i] && input[*i] != '|')
				(*i)++;
		}
		while (is_white_space(input[*i]) && input[*i] != 39 && input[*i] != 34 && input[*i])
			(*i)++;
		if (input[*i] == 39 || input[*i] == 34)
		{
			j = *i;
			(*i)++;
			if (input[j] == 39)
			{
				while (input[*i] != 39 && input[*i])
					(*i)++;
			}
			else if (input[j] == 34)
			{
				while (input[*i] != 34 && input[*i])
					(*i)++;
			}
			if (*i - j > 1 && (input[*i] == 34 || input[*i] == 39))
				ret++;
			else if (input[*i] != 34 && input[*i] != 39)
			{
				write(1, "quotes are open\n", 16);
				return (-1);
			}
			(*i)++;
		}
	}
	if (!input[*i])
		return (ret);
	if (input[*i] == '|' && input[*i + 1] != '|')
	{
		(*i)++;
		data->nb_pipe++;
		while (is_white_space(input[*i]))
			(*i)++;
	}
	else
	{
		printf("Error: pipe\n");
		return (-1);
	}
	if (input[*i] == '|')
	{
		printf("Error: pipe\n");
		return (-1);
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
		while (is_white_space(input[ch]) && input[ch])
			ch++;
		if (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
		{
			while (!is_white_space(input[ch]) && input[ch] != 39 && input[ch] != 34 && input[ch])
			{
				ch++;
				ar++;
			}
			ret[i] = malloc(sizeof(char) * ar + 1);
			if (!ret[i])
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
			if (!ret[i])
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

void	args_check(int *check, char **args, int *builtin)
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
		else if (ft_strcomp("=", args[i]))
			check[6] += 1;
		if (ft_strcomp("cd", args[i]))
			builtin[0] += 1;
		else if (ft_strcomp("export", args[i]))
			builtin[1] += 1;
		else if (ft_strcomp("unset", args[i]))
			builtin[2] += 1;
	}
}

// Variable check[6] :
// 0 = |
// 1-4 = < << >> >
// 5 = $
// Variable builtin[3] :
// 0 = cd
// 1 = export
// 2 = unset

int	access_check(char *cmd, t_prompt *data, int *cmd_iter)
{
	int		i;
	char	*path_cmd;

	i = -1;
	if (!access(cmd, F_OK | X_OK))
	{
		data->cmd_path[*cmd_iter] = "CMD";
		return (1);
	}
	else
	{
		while (data->path[++i])
		{
			path_cmd = ft_strjoin(data->path[i], cmd);
			if (!access(path_cmd, F_OK | X_OK))
			{
				free(path_cmd);
				data->cmd_path[*cmd_iter] = data->path[i];
				return (1);
			}
			free(path_cmd);
		}
	}
	if (ft_strcomp(cmd, "cd") || ft_strcomp(cmd, "export") || ft_strcomp(cmd, "unset"))
	{
		if (ft_strcomp(cmd, "cd"))
			data->cmd_path[*cmd_iter] = "CD_CMD";
		else if (ft_strcomp(cmd, "export"))
			data->cmd_path[*cmd_iter] = "EXPORT_CMD";
		else if (ft_strcomp(cmd, "unset"))
			data->cmd_path[*cmd_iter] = "UNSET_CMD";
		return (1);
	}
	printf("%s: command not found\n", cmd);
	return (0);
}

int	mall_args_check(char *input)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while (input[++i])
	{
		if (input[i] == '|')
		{
			pipe++;
			if (input[i + 1] == '|')
				return (-1);
		}
	}
	return (pipe + 1);
}

void	exit_pars(char ***input)
{
	int	i;
	int	j;

	i = -1;
	if (input[i + 1])
	{
		while (input[++i])
		{
			j = -1;
			if (input[i][j + 1])
				while (input[i][++j])
					free(input[i][j]);
			free(input[i]);
		}
	}
	free(input);
}

char	***parsing(char *input, t_prompt *data)//check args from the stdin (data->prompt)
{
	int			nb_args;
	char		***new_arg;
	int			check[7];
	int			builtin[3];
	int			i;
	int			j;
	int			iter;
	int			cmd_iter;
	int			tmp;

	i = -1;
	iter = 0;
	cmd_iter = 0;
	data->nb_cmd = mall_args_check(input) + 1;
	new_arg = malloc(sizeof(char **) * data->nb_cmd);
	if (!new_arg)
		return (NULL);
	new_arg[data->nb_cmd - 1] = NULL;
	data->cmd_path = malloc(sizeof(char *) * data->nb_cmd);
	if (!data->cmd_path)
	{
		exit_pars(new_arg);
		return (NULL);
	}
	data->cmd_path[data->nb_cmd - 1] = NULL;
	while (++i < mall_args_check(input))
	{
		tmp = iter;
		j = -1;
		nb_args = get_nb_args(input, &iter, data);
		if (nb_args == -1)
		{
			exit_pars(new_arg);
			return (NULL);
		}
		new_arg[i] = malloc(sizeof(char *) * (nb_args + 1));
		if (!new_arg[i])
		{
			exit_pars(new_arg);
			return (NULL);
		}
		new_arg[i] = get_args(new_arg[i], input + tmp, nb_args);
		while (++j < 7)
			check[j] = 0;
		j = -1;
		while (++j < 3)
			builtin[j] = 0;
		args_check(check, new_arg[i], builtin);
		if (!access_check(new_arg[i][0], data, &cmd_iter))
		{
			exit_pars(new_arg);
			return (NULL);
		}
		cmd_iter++;
	}
	return (new_arg);
}
//	return la commande si builtin, return : cd, export ou unset
//						si commande du path, return : "cmd"
//	faire un comp de la chaine return dans execute
//	stocker les arguments dans une chaine place en structure
// 	faire un tableau en 3d pour stocker chaque commandes separe par des pipes
// export / unset, env var
// chercher un '=' ex: poulet=kfc --> prendre la string et la save
// si export implementer cette string dans env[i] (i a determiner)
// si unset retirer string a env[i]
// possibilite d'export une string --> poulet=
// si '=' seul, traite comme une commande
// erreur pour ls si on retire PATH --> bash: ls: No such file or directory


/*
int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	if (ac != 2)
	{
		printf("Error\n");
		return (0);
	}
	char *path = ft_getenv(env, "PATH");

	data.path = give_path(path);
	free(path);
	char	***args = parsing(av[1], &data);
	int		i = 0;
	if (!args)
	{
		while (data.path[i])
		{
			free(data.path[i]);
			i++;
		}
		free(data.path);
		return (0);
	}
	for (int i = 0; args[i]; i++)
	{
		printf("%s ", data.cmd_path[i]);
		for (int j = 0; args[i][j]; j++)
		{
			printf("%s", args[i][j]);
			if (!args[i][j+1])
				printf("\n");
			else
				printf(" ");
		}
		printf("------------\n");
	}
	exit_pars(args);
	i = 0;
	while (data.path[i])
	{
		free(data.path[i]);
		i++;
	}
	free(data.path);
	i = 0;
	free(data.cmd_path);
	return (0);
}*/
