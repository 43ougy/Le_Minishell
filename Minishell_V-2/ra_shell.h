/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:30:18 by abougy            #+#    #+#             */
/*   Updated: 2023/08/26 12:48:53 by abougy           ###   ########.fr       */
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

//STRUCTURES A FAIRE
typedef struct	t_shell
{
		char	*prompt;
		char	**path;
		char	**d_env;
		char	**cmd;
		int		check_exit;
		pid_t	proc;
}	t_prompt;

size_t	ft_strlen(const char *s);
int		ft_strcomp(char *s1, char *s2);
int		ft_strcompn(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
