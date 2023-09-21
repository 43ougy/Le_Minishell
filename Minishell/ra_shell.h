/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:18 by abougy            #+#    #+#             */
/*   Updated: 2023/09/21 12:12:00 by abougy           ###   ########.fr       */
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

typedef struct	t_shell
{
		char	*prompt;
		char	**path;
		char	**d_env;
		char	***cmd;
		char	**cmd_path;
		char	***args;
		int		fd[2];
		int		check_exit;
		int		nb_cmd;
		int		nb_pipe;
		pid_t	proc;
}	t_prompt;

typedef struct	t_signal
{
	const struct sigaction	ctrl_c;
	const struct sigaction	ctrl_b;
}	t_signal;

size_t	ft_strlen(const char *s);
int		ft_strcomp(char *s1, char *s2);
int		ft_strcompn(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strncpy(char *dest, char *src, int n);
char	**split_args(char *args);
int		running(t_prompt *data);
void	execute(t_prompt *data, int i);
void	run_cd(t_prompt *data, char **cmd);
void	exit_exec(t_prompt *data);
void	handle_signal(int signo);
char	*ft_getenv(char **env, char *path_name);
char	**give_path(char *path);
char	***parsing(char *input, t_prompt *data);

#endif
