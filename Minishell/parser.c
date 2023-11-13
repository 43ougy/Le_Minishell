/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:45:37 by abougy            #+#    #+#             */
/*   Updated: 2023/11/10 15:03:09 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_quotes(char *input, int *i, int *len)
{
	int	j;

	j = *i;
	if (input[j] == 34)
	{
		(*i)++;
		while (input[*i] != 34 && input[*i])
			(*i)++;
	}
	else if (input[j] == 39)
	{
		(*i)++;
		while (input[*i] != 39 && input[*i])
			(*i)++;
	}
	if ((*i) - j > 1)
		(*len)++;
	if (input[*i] != 34 && input[*i] != 39)
	{
		write(2, "quotes are open\n", 16);
		return (1);
	}
	(*i)++;
	return (0);
}

int	_give_properties(t_prompt *data, char *input)
{
	int		i;
	int		j;
	int		n;
	char	*path_cmd;

	/*j = 0;
	i = -1;
	data->append = 0;
	data->heredoc = 0;
	if (ft_strcomp(data->cmde[0].cmd[0], " ") && !&data->cmde[1])
	{
		write(1, "\n", 1);
		return (0);
	}*/
	while (++i < data->nb_args)
	{
		/*n = -1;
		while (input[j] && !_is_char(input[j])
			&& input[j] != 34 && input[j] != 39)
			j++;
		if (input[j] == '<' && input[j + 1] != '<' && &data->cmde[i + 1])
		{
			data->cmde[i + 1].infile = 1;
			data->infile = data->cmde[i + 1].cmd[0];
		}
		else if (input[j] == '<' && input[j + 1] == '<' && &data->cmde[i + 1])
		{
			data->cmde[i + 1].infile = 1;
			data->heredoc = 1;
			data->infile = data->cmde[i + 1].cmd[0];
		}
		else if (input[j] == '>' && input[j + 1] != '>' && &data->cmde[i + 1])
		{
			data->cmde[i + 1].outfile = 1;
			data->outfile = data->cmde[i + 1].cmd[0];
		}
		else if (input[j] == '>' && input[j + 1] == '>' && &data->cmde[i + 1])
		{
			data->cmde[i + 1].outfile = 1;
			data->append = 1;
			data->outfile = data->cmde[i + 1].cmd[0];
		}
		else
		{
			while (++n < data->cmde[i].n_inarg)
			{
				if (open(data->cmde[i].cmd[n], O_RDONLY) != -1)
					data->cmde[i].file = 1;
			}
		}*/
		if (!data->cmde[i].infile && !data->cmde[i].outfile)
		{
			n = -1;
			if (!access(data->cmde[i].cmd[0], F_OK | X_OK))
				data->cmde[i].path = "CMD";
			else if (ft_strcomp(data->cmde[i].cmd[0], "cd")
				|| ft_strcomp(data->cmde[i].cmd[0], "export")
				|| ft_strcomp(data->cmde[i].cmd[0], "unset")
				|| ft_strcomp(data->cmde[i].cmd[0], "exit")
				|| ft_strcomp(data->cmde[i].cmd[0], "env"))
				data->cmde[i].path = ft_strdup(data->cmde[i].cmd[0]);
			else if (data->equals > 0)
			{
				if (data->equals == 1 && !data->cmde[i].cmd[1])
					data->cmde[i].path = ft_strdup("set_env");
				else if (data->equals == 1 && data->cmde[i].cmd[1])
					data->cmde[i].path = ft_strdup("bad_set_env");
				else if (data->equals > 1)
					data->cmde[i].path = ft_strdup("bad_set_env");
			}
			else if (data->path)
			{
				while (data->path[++n])
				{
					path_cmd = ft_strjoin(data->path[n], data->cmde[i].cmd[0]);
					if (!access(path_cmd, F_OK | X_OK))
					{
						data->cmde[i].path = ft_strdup(path_cmd);
						free(path_cmd);
						break ;
					}
					free(path_cmd);
				}
			}
			if (!data->cmde[i].path)
			{
				write(2, data->cmde[i].cmd[0], ft_strlen(data->cmde[i].cmd[0]));
				write(2, ": command not found\n", 20);
				if (data->exit_status)
					free(data->exit_status);
				data->exit_status = ft_strdup("127");
				return (1);
			}
		}
		while (input[j] && _is_char(input[j])
			&& input[j] != 34 && input[j] != 39)
			j++;
	}
	return (0);
}

char	*_env_variable(t_prompt *data, char *input)
{
	int		len;
	char	*env_var;
	char	*ret;
	int		i;

	len = 0;
	i = 0;
	while (input[i] && (_is_alpha(input[i]) || input[i] == '_'))
	{
		len++;
		i++;
	}
	env_var = malloc(sizeof(char) * len + 1);
	if (!env_var)
		return (NULL);
	env_var[len] = '\0';
	i = -1;
	while (++i < len)
		env_var[i] = input[i];
	ret = ft_getenv(data->d_env, env_var);
	free(env_var);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*_check_value(t_prompt *data, char *input)
{
	int		i;
	int		j;
	int		ch;
	int		in;
	int		len;
	char	**d_var;
	char	*cmd;

	len = 0;
	j = 0;
	if (data->dollar != -1)
	{
		d_var = malloc(sizeof(char *) * (data->dollar + 1));
		if (!d_var)
			return (NULL);
		d_var[data->dollar] = NULL;
	}
	i = 0;
	while (input[i] && input[i] != ' ' && !_is_quotes(input[i]))
	{
		while (input[i] && (_is_alpha(input[i]) || _is_limiter(input[i])))
		{
			i++;
			len++;
		}
		if (input[i] == '$' && input[i + 1] && (_is_alpha(input[i + 1])
				|| input[i + 1] == '_'))
		{
			d_var[j] = _env_variable(data, input + i + 1);
			if (d_var[j])
				len += ft_strlen(d_var[j]);
			i++;
			while (input[i] && _is_alpha(input[i]))
				i++;
			j++;
		}
		if (input[i] == '$' && ((!_is_alpha(input[i + 1]) && input[i + 1])
				|| !input[i + 1]) && input[i + 1] != '?')
		{
			len++;
			i++;
		}
		if (input[i] == '$' && (input[i + 1] && input[i + 1] == '?'))
		{
			ch = -1;
			while (data->exit_status[++ch])
				len++;
			i += 2;
		}
	}
	cmd = malloc(sizeof(char) * len + 1);
	if (!cmd)
		return (NULL);
	cmd[len] = '\0';
	j = 0;
	i = 0;
	in = 0;
	while (i < len)
	{
		while (i < len && input[in] != '$' && input[in])
		{
			cmd[i] = input[in];
			i++;
			in++;
		}
		if (input[in] == '$' && input[in + 1] && _is_alpha(input[in + 1]))
		{
			ch = -1;
			while (d_var[j] && d_var[j][++ch] && i < len)
			{
				cmd[i] = d_var[j][ch];
				i++;
			}
			in++;
			while (input[in] && _is_alpha(input[in]))
				in++;
			j++;
		}
		if (input[in] == '$' && ((!_is_alpha(input[in + 1]) && input[in + 1])
				|| !input[in + 1]) && input[in + 1] != '?')
		{
			cmd[i] = '$';
			i++;
			in++;
		}
		if (input[in] && input[in] == '$' && (input[in + 1] && input[in + 1] == '?'))
		{
			ch = -1;
			while (data->exit_status[++ch] && i < len)
			{
				cmd[i] = data->exit_status[ch];
				i++;
			}
			in += 2;
		}
	}
	i = -1;
	if (data->dollar != -1)
	{
		while (d_var[++i])
			free(d_var[i]);
		free(d_var);
	}
	return (cmd);
}

int	_get_cmd(t_prompt *data, char *input)
{
	int	i;
	int	save;
	int	n;
	int	j;
	int	args;
	int	in;

	i = -1;
	save = 0;
	j = 0;
	data->equals = 0;
	while (input[j] && input[j] == ' ')
		j++;
	if (!input[j] || input[j] == ' ')
		return (1);
	while (++i < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_args(data, input + save, 0))
			return (1);
		data->cmde[i].n_inarg = data->nb_inar;
		data->cmde[i].cmd = malloc(sizeof(char *) * (data->nb_inar + 1));
		if (!data->cmde[i].cmd)
			return (1);
		data->cmde[i].cmd[data->nb_inar] = NULL;
		args = -1;
		while (++args < data->nb_inar)
		{
			n = 0;
			if (input[j] == 34 || input[j] == 39)
			{
				if (input[j] == 34)
				{
					save = j;
					j++;
					data->dollar = 0;
					in = j - 1;
					while (input[++in] && input[in] != 34)
						if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
							data->dollar++;
					if (data->dollar > 0)
					{
						data->cmde[i].cmd[args] = _check_value(data, input + j);
						if (!data->cmde[i].cmd[args])
							return (1);
						while (input[j] && input[j] != 34)
							j++;
					}
					else
					{
						while (input[j] != 34 && input[j])
						{
							j++;
							n++;
						}
					}
				}
				else if (input[j] == 39)
				{
					save = j;
					j++;
					data->dollar = 0;
					in = j - 1;
					while (input[++in] && input[in] != 39)
						if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
							data->dollar++;
					if (data->dollar > 0)
					{
						data->cmde[i].cmd[args] = _check_value(data, input + j);
						if (!data->cmde[i].cmd[args])
							return (1);
						while (input[j] && input[j] != 39)
							j++;
					}
					else
					{
						while (input[j] != 39 && input[j])
						{
							j++;
							n++;
						}
					}
				}
				if (n)
				{
					data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
					if (!data->cmde[i].cmd[args])
						return (1);
					data->cmde[i].cmd[args] = \
						ft_strncpy(data->cmde[i].cmd[args], input + save + 1, n);
				}
				j++;
				while ((!_is_whitespace(input[j]) || _is_char(input[j]))
					&& input[j] != 34 && input[j] != 39 && input[j])
					j++;
			}
			else
			{
				save = j;
				data->dollar = 0;
				in = save - 1;
				while (input[++in] && input[in] != ' ')
				{
					if (input[in] == '$' && input[in + 1]
							&& _is_alpha(input[in + 1]))
						data->dollar++;
					else if (input[in] == '$' && input[in + 1]
							&& input[in + 1] == '?')
						data->dollar = -1;
				}
				in = save - 1;
				while (input[++in] && input[in] != ' ')
					if (input[in] == '=' && !data->dollar && input[in - 1]
						&& _is_alpha(input[in - 1]) && input[in + 1]
						&& (_is_alpha(input[in + 1]) || input[in + 1] == '/'
							|| _is_num(input[in + 1])))
						data->equals++;
				if (data->dollar > 0 || data->dollar == -1)
				{
					data->cmde[i].cmd[args] = _check_value(data, input + j);
					if (!data->cmde[i].cmd[args])
						return (1);
					while (input[j] && input[j] != ' ')
						j++;
				}
				else
				{
					while (input[j] && !_is_char(input[j]) && input[j] != ' '
						&& input[j] != 34 && input[j] != 39)
					{
						j++;
						n++;
					}
					data->cmde[i].cmd[args] = malloc(sizeof(char) * n + 1);
					if (!data->cmde[i].cmd[args])
						return (1);
					data->cmde[i].cmd[args] = \
					ft_strncpy(data->cmde[i].cmd[args], input + save, n);
				}
				while (input[j] && (!_is_whitespace(input[j])
						|| _is_char(input[j]))
					&& input[j] != 34 && input[j] != 39)
					j++;
			}
			save = j;
		}
	}
	if (_give_properties(data, input))
		return (1);
	return (0);
}

int	_parser(t_prompt *data)
{
	data->nb_pipe = 0;
	data->nb_args = 0;
	data->infile = NULL;
	data->outfile = NULL;
	if (!data->prompt)
		return (1);
	if (_nb_args(data, data->prompt, 1))
		return (1);
	if (_get_cmd(data, data->prompt))
		return (1);
	return (0);
}
/*
int	main(int ac, char **av, char **env)
{
	t_prompt	data;
	char		*path = ft_getenv(env, "PATH");

	(void)ac;
	data.path = give_path(path);
	free(path);
	data.nb_args = 0;
	data.nb_inar = 0;
	data.cmde = NULL;
	data.prompt = av[1];
	//data.prompt = "cat < infile | wc -l | cat -e | husdfhi > outfile";
	_parser(&data);
	for (int i = 0; i < data.nb_args; i++)
	{
		printf("args %d :\n", i);
		for (int j = 0; j < data.cmde[i].n_inarg; j++)
		{
			printf("Infile = ");
			if (data.cmde[i].infile)
				printf("Yes\n");
			else
				printf("No\n");
			printf("Outfile = ");
			if (data.cmde[i].outfile)
				printf("Yes\n");
			else
				printf("No\n");
			printf("Isfile = ");
			if (data.cmde[i].file)
				printf("Yes\n");
			else
				printf("No\n");
			printf("	%s\n", data.cmde[i].cmd[j]);
			if (data.cmde[i].path != NULL)
				printf("Path to [%s] is [%s]\n", data.cmde[i].cmd[0], data.cmde[i].path);
			printf("\n");
		}
	}
	for (int i = 0; data.path[i]; i++)
		free(data.path[i]);
	free(data.path);
	_free_args(&data);
	return (0);
}*/
