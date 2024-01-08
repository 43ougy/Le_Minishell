/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:29:00 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:29:02 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/* ==================== include ==================== */

# include <stdlib.h> /* allocation */
# include <unistd.h> /* input - output */

/* ===================== proto ===================== */

// utils 1
void	*m_freetab(char **tab);
int		m_strlen(const char *s);
char	*m_strdup(const char *s);
void	m_putstr(const char *str, int fd);
char	**m_duplicatetab(char **tab);

// utils 2
int		m_iswhitespace(char c);
void	m_bzero(void *s, int n);
char	*m_strncpy(char *dest, char *src, int n);
int		m_strncmp(const char *s1, const char *s2, int n);
int		m_strcmp(char *s1, char *s2);

// utils 3
char	*m_itoa(int n);
char	**m_split(char const *s, char c);

// utils 4
int		m_tablen(char **tab);
char	**m_endtabpush(char **tab, const char *to_add);

// utils 5
char	*_getenv(char **env, char *path_name);
char	**_give_path(char *path);
char	*_get_path(char *cmd, char **env);
char	*m_strjoin(char *s1, char *s2);
size_t	m_strlcpy(char *dst, const char *src, size_t size);

// utils 6
char	*m_getline(int fd);

// utils 7
int		m_atoi(char *str);
int		m_isalpha(char c);
int		m_isnum(char c);
char	*m_substr(char const *s, unsigned int start, size_t len);
void	*m_calloc(size_t count, size_t size);

#endif
