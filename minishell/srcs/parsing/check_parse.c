#include "parsing.h"

static bool	check_pipe(char *prompt, int i)
{
	int	len;

	len = i + 1;
	while ((!_is_whitespace(prompt[len]) && prompt[len] != '|') && prompt[len])
		len++;
	if (len == (int)_strlen(prompt) || prompt[len] == '|')
	{
		_putstr("bash: parse error near `|'\n", 2);
		return (false);
	}
	i--;
	while ((!_is_whitespace(prompt[i]) && prompt[i] != '|') && i > -1)
		i--;
	if (i == -1 || prompt[i] == '|')
	{
		_putstr("bash: parse error near `|'\n", 2);
		return (false);
	}
	return (true);
}

static bool	check_red(char *prompt, int *i)
{
	bool	status;

	status = true;
	if (!prompt[(*i) + 1] || prompt[(*i) + 1] == '|')
		status = false;
	else if (prompt[(*i) + 1] == '<' || prompt[(*i) + 1] == '>')
	{
		(*i)++;
		if (prompt[(*i)] != prompt[(*i) - 1])
			status = false;
		else if (!prompt[(*i) + 1] || prompt[(*i) + 1] == '|'
			|| prompt[(*i) + 1] == '>' || prompt[(*i) + 1] == '<')
			status = false;
	}
	if (!status)
		_putstr("bash: parse error near `redirection\n", 2);
	return (status);
}

static bool	check_c(char *prompt, int *i, char *edge)
{
	if (*edge == prompt[*i])
		*edge = 0;
	else if (!*edge && (prompt[*i] == '\'' || prompt[*i] == '\"'))
		*edge = prompt[*i];
	else if (!*edge && prompt[*i] == '|')
		return (check_pipe(prompt, *i));
	else if (!*edge && (prompt[*i] == '>' || prompt[*i] == '<'))
		return (check_red(prompt, i));
	return (true);
}

bool	parse_check(char *prompt)
{
	int		i;
	char	edge;

	i = -1;
	edge = 0;
	while (prompt && ++i < (int)_strlen(prompt))
		if (!check_c(prompt, &i, &edge))
			return (false);
	if (edge == 0)
		return (true);
	_putstr("bash: parse error near quote\n", 2);
	return (false);
}
