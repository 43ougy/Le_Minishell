#ifndef EXECUTION_H
# define EXECUTION_H

#include "ra_shell.h"

void	_cmd_laucher(t_parse *parse);
int		_execute(t_parse *parse, int fd_in, int fd_out);

/*=============== builtins ===============*/
int		_cd(t_prompt *data, char **cmd);
int		_echo(char *cmd);
int		_env(char **env);
int		_export(t_prompt *data, int nb_args, char **args);
int		_pwd(void);
int		_unset(t_prompt *data, int nb_args, char **args);
void	_exit(t_parse *parse);

#endif