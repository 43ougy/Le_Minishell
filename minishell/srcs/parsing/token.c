/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:50 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 12:42:26 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

static char	modified_edge(char edge, char c)
{
	if (edge == c)
		return (' ');
	return (c);
}

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
		if (edge == ' ' && (c == ' ' || c == '|'))
			break ;
		else if (c == '\"' || c == '\'')
			edge = modified_edge(edge, c);
		len++;
	}
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	token = _strncpy(token, &prompt[*pos], len);
	(*pos) += len;
	return (token);
}

char	*modified_token(t_prompt data, char *token, t_red **red)
{
	int		pos;
	char	*ret;
	char	edge;

	pos = 0;
	ret = NULL;
	edge = ' ';
	while (token && token[pos])
	{
		if (token[pos] == '\"' || token[pos] == '\'')
			edge = modified_edge(edge, token[pos]);
		else if (token[pos] == '$' && edge != '\'')
			ret = replace_env(ret, data, token, &pos);
		else if (edge == ' ' && (token[pos] == '>' || token[pos] == '<'))
			if (!extract_red(red, token, &pos))
				ret = add_char(ret, token[pos]);
		else
			ret = add_char(ret, token[pos]);
	}
	return (ret);
}

char	*replace_env(char *ret, t_prompt data, char *str, int *pos)
{
	// to do
	return (ret);
}

bool	extract_red(t_red **red, char *str, int *pos)
{
	// to do
	return (true);
}