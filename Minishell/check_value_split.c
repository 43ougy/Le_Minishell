#include "ra_shell.h"

void	_environement_data(t_prompt *data, int *i, char *input, int *j)
{
	data->d_var[*j] = _env_variable(data, input + *i + 1);
	if (data->d_var[*j])
		data->val_len += ft_strlen(data->d_var[*j]);
	(*i)++;
	while (input[*i] && _is_alpha(input[*i]))
		(*i)++;
	(*j)++;
}

void	_exit_status(t_prompt *data, int *i)
{
	int	ch;

	ch = -1;
	while (data->exit_status[++ch])
		data->val_len++;
	(*i) += 2;
}

void	_dollar_attribute(char *input, t_prompt *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->val_len = 0;
	while (input[i] && input[i] != ' ' && !_is_quotes(input[i]))
	{
		while (input[i] && (_is_alpha(input[i]) || _is_limiter(input[i])))
		{
			i++;
			data->val_len++;
		}
		if (input[i] == '$' && input[i + 1] && (_is_alpha(input[i + 1])
				|| input[i + 1] == '_'))
			_environement_data(data, &i, input, &j);
		if (input[i] == '$' && ((!_is_alpha(input[i + 1]) && input[i + 1])
				|| !input[i + 1]) && input[i + 1] != '?')
		{
			i++;
			data->val_len++;
		}
		if (input[i] == '$' && (input[i + 1] && input[i + 1] == '?'))
			_exit_status(data, &i);
	}
}

void	_first_step(t_prompt *data, int *i, int *in, char *input)
{
	while (*i < data->val_len && input[*in] != '$' && input[*in])
	{
		data->d_cmd[*i] = input[*in];
		(*i)++;
		(*in)++;
	}
}

void	_d_var_to_d_cmd(t_prompt *data, int *i, int j)
{
	int	ch;

	ch = -1;
	while (data->d_var[j] && data->d_var[j][++ch] && *i < data->val_len)
	{
		data->d_cmd[*i] = data->d_var[j][ch];
		(*i)++;
	}
}

void	_exit_status_to_d_cmd(t_prompt *data, int *i, int *in)
{
	int	ch;

	ch = -1;
	while (data->exit_status[++ch] && *i < data->val_len)
	{
		data->d_cmd[*i] = data->exit_status[ch];
		(*i)++;
	}
	(*in) += 2;
}

void	_dollar_set(t_prompt *data, int *i, int *in)
{
	data->d_cmd[*i] = '$';
	(*i)++;
	(*in)++;
}

void	_command_attribute(char *input, t_prompt *data)
{
	int	i;
	int	in;
	int	j;

	i = 0;
	in = 0;
	j = 0;
	while (i < data->val_len)
	{
		_first_step(data, &i, &in, input);
		if (input[in] == '$' && input[in + 1] && _is_alpha(input[in + 1]))
		{
			_d_var_to_d_cmd(data, &i, j);
			in++;
			while (input[in] && _is_alpha(input[in]))
				in++;
			j++;
		}
		if (input[in] == '$' && ((!_is_alpha(input[in + 1]) && input[in + 1])
				|| !input[in + 1]) && input[in + 1] != '?')
			_dollar_set(data, &i, &in);
		if (input[in] && input[in] == '$'
			&& (input[in + 1] && input[in + 1] == '?'))
			_exit_status_to_d_cmd(data, &i, &in);
	}
}

void	_init_d_var(t_prompt *data)
{
	data->d_var = malloc(sizeof(char *) * (data->dollar + 1));
	if (!data->d_var)
		return ;
	data->d_var[data->dollar] = NULL;
}

void	_free_d_var(t_prompt *data)
{
	int	i;

	i = -1;
	while (data->d_var[++i])
		free(data->d_var[i]);
	free(data->d_var);
}

char	*_check_value(t_prompt *data, char *input)
{
	data->d_var = NULL;
	data->d_cmd = NULL;
	if (data->dollar)
	{
		_init_d_var(data);
		if (!data->d_var)
			return (NULL);
	}
	_dollar_attribute(input, data);
	data->d_cmd = malloc(sizeof(char) * data->val_len + 1);
	if (!data->d_cmd)
		return (NULL);
	data->d_cmd[data->val_len] = '\0';
	_command_attribute(input, data);
	if (data->dollar)
		_free_d_var(data);
	return (data->d_cmd);
}
