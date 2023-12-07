/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:16:54 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 15:49:19 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*=============== string =================*/
int		_strcomp(char *s1, char *s2);
int		_strcompn(char *s1, char *s2, int n);
char	*_strjoin(char *s1, char *s2);
char	*_substr(char const *s, unsigned int start, size_t len);
char	*_strdup(const char *s);
size_t	_strlcpy(char *dst, const char *src, size_t size);
char	*_strncpy(char *dest, char *src, int n);
int		_comp(char *s1, char *s2);
void	_putstr(const char *str, int fd);

/*=============== utils ==================*/
int		_atoi(char *str);
void	_bzero(void *s, size_t n);
size_t	_strlen(const char *s);
char	**_duplicate_tab(char **tab);
int		_tblen(char **tab);

/*=============== check_char =============*/
int		_is_quotes(char c);
int		_is_char(char c);
int		_is_num(char c);
int		_is_alpha(char c);
int		_is_limiter(char c);
int		_is_whitespace(char c);

/*=============== alloc ==================*/
//void	_free_args(t_prompt *data, int status);
void	*_free_tab(char **tab);
void	_free(char *string);
void	*_calloc(size_t count, size_t size);
char	**_endtab_push(char **tab, char *to_add);

/*=============== path ===================*/
char	*_getenv(char **env, char *path_name);
char	**_give_path(char *path);
char	*_get_path(char *cmd, char **env);

char	*get_line(int fd);
char	**_split(char const *s, char c);
char	*_itoa(int n);

#endif
