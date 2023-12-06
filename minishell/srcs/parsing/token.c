#include "ra_shell.h"

static char	modified_edge(char edge, char c)
{
	if (edge == c)
		return (' ')
	return (c);
}

// si $ continue jusqu'a > or <
// echo "$PA>test" -> (>test) -> one token
// echo "test | test" -> (test | test) -> one token
char	*extract_token(char *prompt, int *pos)
{
	int		len;
	char	edge;
	char	c;

	len = 0;
	edge = ' ';
	while (prompt && prompt[(*pos) + len])
	{
		c = prompt[(*pos) + len];
		if (edge == ' ' && c == ' ')
			break ;
		else if (c == '\"' || c == '\'')
			edge = modified_edge(edge, c);
		len++;
	}
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	(*pos) += len;
	return (_strncpy(token, &prompt[*pos], len));
}

char	*modified_token(char *token, t_red *red, int *status)
{
	char	*ret;

	ret = NULL;
}