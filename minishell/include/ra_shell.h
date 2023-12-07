/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:16:47 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 16:14:29 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RA_SHELL_H
# define RA_SHELL_H

/* ==================== include ==================== */
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>

# include "utils.h"

/* ===================== struct ==================== */
typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
	int		file;
	int		n_inarg;
}	t_cmd;

typedef struct s_run
{
	char	*comp;
	char	*equal;
	char	*name;
	int		len;
	int		i;
	int		j;
}	t_run;

typedef struct s_shell
{
	char	*prompt;
	char	**path;
	char	**d_env;
	t_cmd	*cmde;
	int		nb_args;
	int		nb_inar;
	char	*infile;
	char	*outfile;
	char	**set_env;
	int		exec_check;
	int		background;
	int		fd[2];
	int		tmpin;
	int		tmpout;
	int		fdin;
	int		fdout;
	int		check_exit;
	int		question_mark;
	int		args_count;
	int		cmd_count;
	int		index;
	int		i;
	int		i_check;
	int		save_index;
	int		cmd_len;
	int		val_len;
	int		dollar;
	int		equals;
	char	**d_var;
	char	*d_cmd;
	char	*exit_status;
	int		nb_pipe;
	int		status;
	int		append;
	int		heredoc;
	int		quit_cmd_pipe;
	int		input_len;
	pid_t	proc;
}	t_prompt;

# include "parsing.h"
/* ===================== proto ===================== */
int	running(t_prompt *data);

#endif
