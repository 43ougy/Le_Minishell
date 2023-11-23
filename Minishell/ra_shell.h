/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:18 by abougy            #+#    #+#             */
/*   Updated: 2023/11/23 14:56:23 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RA_SHELL_H
# define RA_SHELL_H

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

typedef struct t_signal
{
	const struct sigaction	ctrl_c;
	const struct sigaction	ctrl_b;
}	t_signal;

typedef struct t_cmd
{
	char	**cmd;
	char	*path;
	int		infile;
	int		outfile;
	int		file;
	int		n_inarg;
}	t_cmd;

typedef struct t_run
{
	int		len;
	int		i;
	int		j;
	char	*comp;
	char	*equal;
}	t_run;

typedef struct t_shell
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
	int		nb_pipe;
	char	**d_var;
	char	*d_cmd;
	char	*exit_status;
	int		status;
	int		append;
	int		heredoc;
	pid_t	proc;
}	t_prompt;

//============Utils===========//
size_t	ft_strlen(const char *s);
int		ft_strcomp(char *s1, char *s2);
int		ft_strcompn(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strncpy(char *dest, char *src, int n);
int		ft_atoi(char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	handle_signal(int signo);
char	*ft_getenv(char **env, char *path_name);
char	**give_path(char *path);

//===========Parser===========//
int		_is_quotes(char c);
int		_is_char(char c);
int		_is_num(char c);
int		_is_alpha(char c);
int		_is_limiter(char c);
int		_is_whitespace(char c);
char	*_env_variable(t_prompt *data, char *input);
int		_nb_args(t_prompt *data, char *input, int method);
int		_give_properties(t_prompt *data, char *input);
char	*_check_value(t_prompt *data, char *input);
int		_get_cmd(t_prompt *data, char *input);
void	_free_args(t_prompt *data, int status);
void	_free_args_nexit(t_prompt *data);
void	_free_struct(t_prompt *data);
int		_quotes(char *input, int *i, int *len);
int		_parser(t_prompt *data);

//==========Get_Line==========//
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_free(char *buffer, char *buf);
char	*cat_line(char *line);
char	*read_stdin(int fd, char *line);
char	*get_line(int fd);

//=============Run============//
char	**run_export(t_prompt *data, char *name);
char	**run_unset(t_prompt *data, char *name);
char	**run_set_equals(t_prompt *data, char *input);
int		running(t_prompt *data);
void	run_env(t_prompt *data);
void	run_cd(t_prompt *data, char **cmd);
void	run_pwd(void);
void	run_echo(t_prompt *data, int i);

//========Check_value=========//
void	_environement_data(t_prompt *data, int *i, char *input, int *j);
void	_exit_status(t_prompt *data, int *i);
void	_dollar_attribute(char *input, t_prompt *data);
void	_first_step(t_prompt *data, int *i, int *in, char *input);
void	_d_var_to_d_cmd(t_prompt *data, int *i, int j);
void	_exit_status_to_d_cmd(t_prompt *data, int *i, int *in);
void	_dollar_set(t_prompt *data, int *i, int *in);
void	_command_attribute(char *input, t_prompt *data);

//=========Execution==========//
void	execute(t_prompt *data, int i);
int		_execution(t_prompt *data);
int		_infile_check(t_prompt *data);
void	_outfile_check(t_prompt *data);
void	_fd_check_in_pipe(t_prompt *data);
int		_when_no_line(t_prompt *data, char *ret);
int		_heredoc_command(t_prompt *data, char *ret);
int		_heredoc_check(t_prompt *data);
void	_child_process(t_prompt *data);
void	_reset_redirect(t_prompt *data);
void	_exit_cmd(t_prompt *data, int status);
void	_cmd_execution(t_prompt *data, int status);

//===========Nb_args==========//
int		_token_check_error(char *input, t_prompt *data);
int		_check_chevron_error(char *input, int *j);
int		_check_rchevron_error(char *input, int *j);
void	_input_first_check(char *input, int *i, t_prompt *data);
void	_cmd_pipe_input(char *input, char *new_input, t_prompt *data);
void	_cmd_pipe(char *input, t_prompt *data);
int		_check_pipe_error(char *input, int *i, t_prompt *data);
int		_check_quotes_error(char *input, int *in, \
int check_char, t_prompt *data);
int		_input_check_error(char *input, t_prompt *data);
void	_init_cmde(t_prompt *data);

//======Give_properties======//
void	_infile_chevron(t_prompt *data, int i);
void	_outfile_chevron(t_prompt *data, int i);
void	_chevron_file(t_prompt *data, int i, int j, char *input);

//==========Get_cmd==========//
int		_space_checker(t_prompt *data, char *input);
int		_nb_cmd_check(t_prompt *data, char *input);
void	_set_data_value(t_prompt *data);
int		_when_dollar(t_prompt *data, char *input, int quotes);
int		_when_dollar_no_quotes(t_prompt *data, char *input);
int		_quotes_dollar_check(t_prompt *data, char *input, int quotes);
int		_when_quotes(t_prompt *data, char *input);
void	_equals_check(t_prompt *data, char *input);
int		_cmd_init(t_prompt *data, char *input);
int		_dollar_equals_check(t_prompt *data, char *input);

#endif
