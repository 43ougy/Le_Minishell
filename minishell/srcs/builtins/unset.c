#include "execution.h"

static int	is_env(char *env, char *name)
{
	int	i;

	i = 0;
	while ((env[i] && name[i]) && (env[i] == name[i]))
		i++;
	if (env[i] && name[i])
		return (0);
	return (1);
}

static void	remove_env(int i)
{
	free(g_glob.env[i]);
	while (data->d_env[i + 1])
	{
		data->d_env[idx] = data->d_env[i + 1];
		i++;
	}
	data->d_env[i] = NULL;
}

int	_unset(int nb_args, char **args)
{
	int	i;

	i = 0;
	if (nb_args != 2)
		return (42);
	while (data->d_env[i] && !is_env(data->d_env[i], args[1]))
		i++;
	if (!data->d_env[i])
		return (1);
	remove_env(i);
	return (0);
}