#include "ra_shell.h"

int	_is_char(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 34 || c == 39)
		return (1);
	return (0);
}

int	_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (0);
	return (1);
}

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
			write(1, "quotes are open\n", 16);
			return (1);
	}
	(*i)++;
	return (0);
}

int	_nb_args(t_prompt *data, char *input, int method)
{
	int	i;
	int	nb_args;

	i = 0;
	nb_args = 0;
	if (method)
	{
		while (input[i])
		{
			if (!_is_char(input[i]) && input[i] != ' ')
			{
				nb_args++;
				while (!_is_char(input[i]) && input[i] != ' ' && input[i])
					i++;
			}
			while (input[i] == ' ' && !_is_char(input[i]))
				i++;
			while (_is_char(input[i]) && input[i] != 34 && input[i] != 39 && input[i])
				i++;
			if (input[i] == 34 || input[i] == 39)
				if (_quotes(input, &i, &nb_args))
					return (1);
		}
		data->cmde = malloc(sizeof(t_cmd) * nb_args + 1);
		if (!data->cmde)
			return (1);
		data->nb_args = nb_args;
	}
	else if (!method)
	{
		if (input[i] == 34 || input[i] == 39)
		{
			printf("tset\n");
			if (_quotes(input, &i, &nb_args))
				return (1);
			printf("%d\n", data->nb_inar);
		}
		else
		{
			while (input[i] && !_is_char(input[i]))
			{
				if (input[i] != ' ' && input[i] != 34 && input[i] != 39)
				{
					nb_args++;
					while (!_is_char(input[i]) && input[i] != ' ' && input[i])
						i++;
				}
				while (input[i] == ' ' && !_is_char(input[i]) && input[i] != 34 && input[i] != 39)
					i++;
				if (input[i] == 34 || input[i] == 39)
					if (_quotes(input, &i, &nb_args))
						return (1);
			}
		}
		data->nb_inar = nb_args;
	}
	return (0);
}

int	_get_cmd(t_prompt *data, char *input)
{
	int	i;
	int	save;
	int	n;
	int	j;
	int	args;

	i = -1;
	save = 0;
	j = 0;
	while (++i < data->nb_args)
	{
		data->nb_inar = 0;
		if (_nb_args(data, input + save, 0))
			return (1);
		printf("%c, save = %d, nb_inar = %d\n", input[save], save, data->nb_inar);
		data->cmde[i].cmd = malloc(sizeof(char *) * data->nb_inar);
		if (!data->cmde[i].cmd)
			return (1);
		args = -1;
		while (++args < data->nb_inar)
		{
			n = 0;
			if (input[j] == 34 || input[j] == 39)
			{
				if (input[j] == 34)
				{
					j++;
					while (input[j] != 34 && input[j])
					{
						j++;
						n++;
					}
				}
				if (input[j] == 39)
				{
					j++;
					while (input[j] != 39 && input[j])
					{
						j++;
						n++;
					}
				}
				data->cmde[i].cmd[args] = malloc(sizeof(char) * n);
				if (!data->cmde[i].cmd[args])
					return (1);
				data->cmde[i].cmd[args] = ft_strncpy(data->cmde[i].cmd[args], input + save + 1, n);
				data->cmde[i].cmd[args][n] = '\0';
				j++;
				while ((!_is_whitespace(input[j]) || _is_char(input[j])) && input[j] != 34 && input[j] != 39)
					j++;
			}
			else
			{
				while (input[j] && input[j] == ' ')
					j++;
				while (input[j] && !_is_char(input[j]) && input[j] != ' ')
				{
					j++;
					n++;
				}
				data->cmde[i].cmd[args] = malloc(sizeof(char) * n);
				if (!data->cmde[i].cmd[args])
					return (1);
				data->cmde[i].cmd[args] = ft_strncpy(data->cmde[i].cmd[args], input + save, n);
				data->cmde[i].cmd[args][n] = '\0';
				while ((!_is_whitespace(input[j]) || _is_char(input[j])) && input[j] != 34 && input[j] != 39)
					j++;
			}
			save = j;
		}
	}
	return (0);
}
/*
void	_free_args(t_prompt *data)
{
	int	i;
	int	j;

	if (data->cmde)
	{
		i = -1;
		while (++i < data->nb_args)
		{
			j = -1;
			if (data->cmde[i].cmd)
			{
				while (data->cmde[i].cmd[++j])
					free(data->cmde[i].cmd[j]);
				free(data->cmde[i].cmd);
			}
			if (data->cmde[i].path)
				free(data->cmde[i].path);
		}
		free(data->cmde);
	}
}*/

int	_parser(t_prompt *data)
{
	if (_nb_args(data, data->prompt, 1))
		return (1);
	printf("args = %d, inar = %d\n", data->nb_args, data->nb_inar);
	if (_get_cmd(data, data->prompt))
		return (1);
	return (0); 
}

int	main()
{
	t_prompt	data;

	data.nb_args = 0;
	data.nb_inar = 0;
	data.cmde = NULL;
	data.prompt = "cat < \" infile | wc -l | cat -e >\" outfile";
	_parser(&data);
	for (int i = 0; i < data.nb_args; i++)
	{
		printf("args %d :\n", i);
		for (int j = 0; data.cmde[i].cmd[j]; j++)
			printf("	%s\n", data.cmde[i].cmd[j]);
	}
	if (data.cmde)
		free(data.cmde);
//	_free_args(&data);
	return (0);
}
