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
			return (NULL);
		parse = add_parse(parse, red, cmd);
	}
	return (parse);
}


char	**extract_cmd(t_prompt *data, int *pos, t_red **red)
{
	char	**cmd;

	// to do
	// exctract_token()
	return (cmd);
}