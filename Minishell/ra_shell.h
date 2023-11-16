/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:18 by abougy            #+#    #+#             */
/*   Updated: 2023/11/16 15:14:42 by abougy           ###   ########.fr       */
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
	int		check_exit;
	int		question_mark;
	int		dollar;
	int		equals;
	int		nb_pipe;
	char	**d_var;
	char	*d_cmd;
	char	*exit_status;
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

//===========Prompt===========//
int		running(t_prompt *data);
void	execute(t_prompt *data, int i);
void	run_env(t_prompt *data);
void	run_cd(t_prompt *data, char **cmd);
char	**run_export(t_prompt *data, char *name);
char	**run_unset(t_prompt *data, char *name);
char	**run_set_equals(t_prompt *data, char *input);
void	handle_signal(int signo);
char	*ft_getenv(char **env, char *path_name);
char	**give_path(char *path);
int		_execution(t_prompt *data);

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

#endif
