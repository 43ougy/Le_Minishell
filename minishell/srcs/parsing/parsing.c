#include "ra_shell.h"

static bool	error_in_parsing(t_red *red, char **cmd)
{
	if (!red || !cmd)
	{
		free_red(red);
		_free_tab(cmd);
		return (true);
	}
	return (false);
}

t_parse	*parse(t_prompt *data, char *ret_value)
{
	int		pos;
	char	**cmd;
	t_red	*red;
	t_parse	*parse;

	loop = 0;
	parse = NULL;
	while (pos < _strlen(data->prompt)) {
		red = NULL;
		cmd = extract_cmd(data, &pos, &red);
		if (error_in_parsing(red, cmd))
			return (free_list(begin, 0));
		parse = add_parse(parse, red, cmd);
	}
	return (parse);
}

void	*print_parse_error(char *prompt, int pos, char **cmd)
{
	int	i;

	i = -1;
	if (prompt[pos] == '|')
	{
		write(2, &prompt[0], _strlen(prompt));
		while (++i < pos)
			write(2, " ", 1);
		write(2, "^\nnothing between pipe\n", 23);
	}
	_free_tab(cmd);
	return (NULL);
}

char	**extract_cmd(t_prompt *data, int *pos, t_red **red)
{
	int		len;
	char	*token;
	char	**cmd;
	int		status;

	cmd = NULL;
	status = 0;
	while (data->prompt && data->prompt[*pos] != '|')
	{
		while (data->prompt && _is_whitespace(data->prompt[*pos]))
			(*pos)++;
		if (!data->prompt[*pos] || data->prompt[*pos] != '|') // nothing on line
			return (print_parse_error(data->prompt, *pos, cmd))
		token = extract_token(data->prompt, pos); // extract the token (tes"$PATH >alpha"'alpha')
		token = modified_token(token, red, &status); // set red
		if (!status) // if extract token failed
			return (_free_tab(cmd));
		cmd = _endtab_push(cmd, token); // add the token to the tab
		if (!cmd)
			return (_free_tab(cmd));
	}
	return (cmd);
}

// si $ continue jusqu'a > or <
// echo "$PA>test" -> (>test) -> one token
// echo "test | test" -> (test | test) -> one token
char	*extract_token(char *prompt, int *pos)
{
	char	*token;
	char	edge;

	edge = ' ';
	token = NULL;
	return (token);
}

char	*modified_token(char *token, t_red *red, int *status)
{
	// to do
}