#ifndef UTILS_H
# define UTILS_H

size_t	_strlen(const char *s);
int		_strcomp(char *s1, char *s2);
int		_strcompn(char *s1, char *s2, int n);
char	*_strjoin(char *s1, char *s2);
char	**_split(char const *s, char c);
char	*_itoa(int n);
char	*_substr(char const *s, unsigned int start, size_t len);
char	*_strdup(const char *s);
size_t	_strlcpy(char *dst, const char *src, size_t size);
char	*_strncpy(char *dest, char *src, int n);
int		_atoi(char *str);
void	_bzero(void *s, size_t n);
void	*_calloc(size_t count, size_t size);
int		_comp(char *s1, char *s2);
int		_is_quotes(char c);
int		_is_char(char c);
int		_is_num(char c);
int		_is_alpha(char c);
int		_is_limiter(char c);
int		_is_whitespace(char c);
char	**_duplicate_tab(char **tab);
void	_free_tab(char **tab);

#endif