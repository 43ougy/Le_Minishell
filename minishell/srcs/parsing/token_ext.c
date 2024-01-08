/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:30:50 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:30:51 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find if the variable exist in env 
char	*find_var(char **env, char *token, int len)
{
	int		i;
	char	*ret;
	char	**split_env;

	i = -1;
	ret = NULL;
	while (!ret && env && env[++i])
	{
		split_env = m_split(env[i], '=');
		if (!split_env)
			return (NULL);
		if (!m_strncmp(split_env[0], token, len))
			ret = m_strdup(split_env[1]);
		m_freetab(split_env);
	}
	return (ret);
}

// find the type of redirection
static int	get_red_type(char *token)
{
	if (token[1] == '>')
		return (4);
	else if (token[1] == '<')
		return (2);
	else if (token[0] == '>')
		return (3);
	else
		return (1);
}

// add the file name to the t_red struct
static void	add_red(t_red *red, int type, char *filename)
{
	if (type == 1)
		red->input1 = m_endtabpush(red->input1, filename);
	else if (type == 2)
		red->input2 = m_endtabpush(red->input2, filename);
	else if (type == 3)
		red->output1 = m_endtabpush(red->output1, filename);
	else if (type == 4)
		red->output2 = m_endtabpush(red->output2, filename);
}

// get the file name
static int	get_red(t_red *red, char *token)
{
	int		i;
	char	tmp;
	t_var	var;

	i = get_red_type(token) % 2;
	if (!i)
		i = 2;
	m_bzero(&var, sizeof(t_var));
	var.edge = ' ';
	while (token && token[i])
	{
		if (var.edge == ' ' && (token[i] == '<' || token[i] == '>'))
			break ;
		else if (token[i] == '\"' || token[i] == '\'')
		{
			tmp = var.edge;
			var.edge = modified_edge(var.edge, token[i++]);
			if (tmp != var.edge)
				continue ;
		}
		var.new_token[var.idx++] = token[i++];
	}
	add_red(red, get_red_type(token), var.new_token);
	return (i);
}

// remove the redirection and the quotes of the token
char	*manage_red(t_red *red, char *token)
{
	int		i;
	char	tmp;
	t_var	var;

	i = -1;
	t_varinit(&var);
	while (++i < m_strlen(token) && var.idx < TOKEN_MAX_SZ)
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			tmp = var.edge;
			var.edge = modified_edge(var.edge, token[i]);
			if (tmp != var.edge)
				continue ;
		}
		if (var.edge == ' ' && (token[i] == '>' || token[i] == '<'))
			i += get_red(red, &token[i]);
		else
			var.new_token[var.idx++] = token[i];
	}
	return (m_strdup(var.new_token));
}
