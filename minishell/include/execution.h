#ifndef EXECUTION_H
# define EXECUTION_H

#include "ra_shell.h"

void	_cmd_laucher(t_parse *parse);
int		_execute(t_parse *parse, int fd_in, int fd_out);

#endif