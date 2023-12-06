#include "execution.h"

static char	**_sort_new_env(char **new_env)
{
	int		i;
	int		j;
	char	*tmp;
	
	i = -1;
	while (new_env[++i])
	{
		j = -1;
		while (new_env[++j + 1])
		{
			if (_comp(new_env[i], new_env[j]) < 0)
			{
				tmp = new_env[i];
				new_env[i] = new_env[j];
				new_env[j] = tmp;
			}
		}
	}
	return (new_env);
}

static void	_sort_env(t_prompt *data)
{
	char	**new_env;
	int		i;

	i = -1;
	if (!data->d_env)
		return ;
	new_env = _duplicate_tab(data->d_env);
	if (!new_env)
		return ;
	new_env = _sort_new_env(new_env);
	while (new_env[++i])
	{
		write(1, "declare -x ", 11);
		write(1, new_env[i], ft_strlen(new_env[i]));
		write(1, "\n", 1);
		free(new_env[i]);
	}
	free(new_env);
}

static int	_valid_args(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
		return (0);
	return(1)
}

int	_export(int nb_args, char **args)
{
	if (nb_args > 2)
		return (1);
	if (nb_args == 1)
		r_sort_env();
	else if (!_valid_args(args[1]))
		data->d_env = _endtab_push(data->d_env, args[1]);
	else
		return (1);
	return (0);
}