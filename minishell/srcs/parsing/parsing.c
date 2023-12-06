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

// ls -l>test| pwd | cat
// [ls][-l]
// red -> outup1 [test] 

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

// agrandir la fonction + incrementer pos pour le pipe
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
		// go up
		token = extract_token(data->prompt, pos); // extract the token (tes"$PATH >alpha"'alpha'>file1)
		if (!token)
			return (_free_tab(cmd));
		token = modified_token(token, red, &status); // set red
		if (!status) // if extract token failed
			return (_free_tab(cmd));
		cmd = _endtab_push(cmd, token); // add the token to the tab
		if (!cmd)
			return (_free_tab(cmd));
	}
	return (cmd);
}

bool	quote_check(char *prompt)
{
	int		i;
	char	edge;

	i = -1;
	edge = 0;
	while (prompt && prompt[++i])
	{
		if (edge == prompt[i])
			edge = 0;
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			edge = prompt[i];
	}
	if (edge == 0)
		return (true);
	write(2, "unexpected quote\n", 17);
	return (false);
}