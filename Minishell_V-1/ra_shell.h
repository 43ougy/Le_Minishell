/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:00:36 by abougy            #+#    #+#             */
/*   Updated: 2023/07/12 11:47:13 by abougy           ###   ########.fr       */
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

typedef struct t_shell
{
	char	*prompt;
	char	**path;
	char	*p;
	pid_t	pid;
}	s_shell;

int		ft_strlen(char *str);
int		ft_strcomp(char *s1, char *s2);
int		verify_command(char *cmd, char *path);
int		ft_strcompn(char *s1, char *s2, int n);
char	**get_env(void);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	run_command(char **path, char **env, char *p);

#endif
