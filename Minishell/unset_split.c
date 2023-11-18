#include "ra_shell.h"

void	_comp_d_env(t_prompt *data, t_run *run, char *name)
{
	int	len;
	int	j;

	len = -1;
	run->i = 0;
	run->comp = NULL;
	while (data->d_env[++len])
	{
		j = 0;
		while (data->d_env[len][j] && data->d_env[len][j] != '=')
			j++;
		run->comp = ft_substr(data->d_env[len], 0, j);
		if (ft_strcomp(name, run->comp))
		{
			free(run->comp);
			run->comp = ft_strdup(data->d_env[len]);
			run->i = -1;
			break ;
		}
		free(run->comp);
	}
}

void	_d_env_len(t_prompt *data, t_run *run)
{
	run->len = 0;
	while (data->d_env[run->len])
		run->len++;
}

char	**_reset_env(t_prompt *data, t_run *run, char **new_env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (data->d_env[++i])
	{
		if (data->d_env[i] && !ft_strcomp(data->d_env[i], run->comp))
		{
			printf("[%d]\n", i);
			new_env[j] = ft_strdup(data->d_env[i]);
			j++;
		}
		else
			printf("[%s] | [%s] | [%d]\n", data->d_env[i], run->comp, i);
	}
	new_env[j] = NULL;
	i = -1;
	while (data->d_env[++i])
		free(data->d_env[i]);
	free(data->d_env);
	free(run->comp);
	data->d_env = NULL;
	return (new_env);
}

char	**run_unset(t_prompt *data, char *name)
{
	t_run	run;
	char	**new_env;

	new_env = NULL;
	if (!name)
		return (data->d_env);
	_comp_d_env(data, &run, name);
	if (run.i != -1)
		return (data->d_env);
	_d_env_len(data, &run);
	new_env = malloc(sizeof(char *) * run.len);
	if (!new_env)
		return (NULL);
	new_env = _reset_env(data, &run, new_env);
	return (new_env);
}
