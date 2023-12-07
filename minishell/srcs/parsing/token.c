/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:19:50 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 15:25:07 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

static char	modified_edge(char edge, char c)
{
	if (edge == c)
		return (' ');
	return (c);
}

static int	find_red_type(char *str, int pos)
{
	if (str[pos + 1] == '>')
		return (4);
	else if (str[pos + 1] == '<')
		return (2);
	else if (str[pos] == '>')
		return (3);
	else if (str[pos] == '<')
		return (1);
	return (0);
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
			extract_red(red, token, &pos);
		else
			ret = add_char(ret, token[pos++]);
	}
	return (ret);
}

// echo test >test"alpha" -> file_name = testalpha
void	extract_red(t_red **red, char *str, int *pos)
{
	char	edge;
	int		len;
	int		red_type;
	char	buff[BUFFER_SIZE];

	_bzero((void *)&buff[0], BUFFER_SIZE);
	red_type = find_red_type(str, *pos);
	if (red_type == 4 || red_type == 2)
		(*pos)++;
	while (str[*pos + len])
	{
		if (str[*pos + len] == )
		buff[len] = str[*pos + len];
		len++;
	}
	// tab = _endtab_push(tab, buff);
}