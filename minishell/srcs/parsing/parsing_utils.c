/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:30:36 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:30:38 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	modified_edge(char edge, char c)
{
	if (edge == c)
		return (' ');
	return (c);
}

void	free_red(t_red *red)
{
	m_freetab(red->input1);
	m_freetab(red->input2);
	m_freetab(red->output1);
	m_freetab(red->output2);
	free(red);
}

void	t_varinit(t_var *var)
{
	var->idx = 0;
	var->edge = ' ';
	m_bzero(&var->new_token[0], TOKEN_MAX_SZ);
}

static int	count_empty(char **tab)
{
	int	i;
	int	ret;
	int	tablen;

	i = -1;
	ret = 0;
	tablen = m_tablen(tab);
	while (tab && tab[++i])
	{
		if (!m_strlen(tab[i]))
			ret++;
	}
	if (!tablen && !ret)
		return (1);
	return (tablen - ret);
}

// remove empty string in an array of string
char	**tabremoveempty(char **cmd)
{
	int		i;
	int		idx;
	char	**ret;

	ret = malloc(sizeof(char *) * (count_empty(cmd) + 1));
	if (!ret)
		return (cmd);
	i = -1;
	idx = 0;
	while (cmd && cmd[++i])
	{
		if (!m_strlen(cmd[i]))
			free(cmd[i]);
		else
			ret[idx++] = cmd[i];
	}
	if (!idx)
		ret[idx++] = m_strdup("");
	ret[idx] = NULL;
	free(cmd);
	return (ret);
}
