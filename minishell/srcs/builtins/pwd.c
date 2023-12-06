#include "execution.h"

int	_pwd(void)
{
	char	location[1024];

	if (!getcwd(location, sizeof(location)))
	{
		perror("pwd");
		return (1);
	}
	write(1, location, ft_strlen(location));
	write(1, "\n", 1);
	return (0);
}