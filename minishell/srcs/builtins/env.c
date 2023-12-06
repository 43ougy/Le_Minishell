#include "execution.h"

int	_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
	}
	return (0);
}