#ifndef EXECUTION_H
# define EXECUTION_H

#include "ra_shell.h"

void	_cmd_laucher(t_parse *parse);
int		_execute(t_parse *parse, int fd_in, int fd_out);

/*=============== builtins ===============*/
int		_cd(t_prompt *data, char **cmd);
int		_echo(t_prompt *data, int i);
int		_env(t_prompt *data);
int		_export(int nb_args, char **args);
int		_pwd(void);
int		_unset(int nb_args, char **args);
void	_exit(t_prompt *data, int status);

#endif