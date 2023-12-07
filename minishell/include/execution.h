/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:16:27 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:16:31 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "ra_shell.h"

void	_cmd_launcher(t_parse *parse, t_prompt *data);
int		_execute(t_parse *parse, t_prompt *data, int fd_in, int fd_out);

/*=============== builtins ===============*/
int		_cd(t_prompt *data, char **cmd);
int		_echo(char *cmd);
int		_env(char **env);
int		_export(t_prompt *data, int nb_args, char **args);
int		_pwd(void);
int		_unset(t_prompt *data, int nb_args, char **args);
void	_exit(t_parse *parse);

/*=============== redirect ===============*/
int		*_out_red(t_red *red);

#endif
