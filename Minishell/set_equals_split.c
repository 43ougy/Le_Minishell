#include "ra_shell.h"

void	_comp_name_set_env(t_prompt *data, t_run *run, char *name, char *input)
{
	int	j;

	while (data->set_env[++run->len])
	{
		j = 0;
		while (data->set_env[run->len][j] && data->set_env[run->len][j] != '=')
			j++;
		run->comp = ft_substr(data->set_env[run->len], 0, j);
		if (ft_strcomp(name, run->comp))
		{
			free(run->comp);
			free(name);
			free(data->set_env[run->len]);
			data->set_env[run->len] = ft_strdup(input);
			run->i = -1;
			return ;
		}
		free(run->comp);
	}
	free(name);
}

void	_check_equals(t_prompt *data, t_run *run, char *input)
{
	char	*name;
	int		j;

	run->comp = NULL;
	while (data->set_env[run->len])
	{
		if (ft_strcomp(data->set_env[run->len], input))
		{
			run->i = -1;
			return ;
		}
		run->len++;
	}
	run->len = -1;
	j = 0;
	while (input[j] && input[j] != '=')
		j++;
	name = ft_substr(input, 0, j);
	_comp_name_set_env(data, run, name, input);
}

char	**_set_ret(t_prompt *data, t_run *run, char **ret)
{
	run->j = -1;
	ret = malloc(sizeof(char *) * (run->len + 2));
	if (!ret)
		return (NULL);
	if (data->set_env)
	{
		while (++run->j < run->len && data->set_env[run->j])
		{
			ret[run->j] = ft_strdup(data->set_env[run->j]);
			free(data->set_env[run->j]);
		}
		free(data->set_env);
	}
	return (ret);
}

char	**run_set_equals(t_prompt *data, char *input)
{
	char	**ret;
	t_run	run;

	ret = NULL;
	run.i = 0;
	run.len = 0;
	if (data->set_env)
	{
		_check_equals(data, &run, input);
		if (run.i == -1)
			return (data->set_env);
	}
	ret = malloc(sizeof(char *) * (run.len + 2));
	if (!ret)
		return (NULL);
	if (data->set_env)
		ret = _set_ret(data, &run, ret);
	ret[run.len] = ft_strdup(input);
	ret[run.len + 1] = NULL;
	if (!ret)
		return (NULL);
	return (ret);
}
