/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:30:17 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:30:19 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_list(t_parse *ptr, int option)
{
	t_parse	*tmp;

	while (ptr)
	{
		tmp = ptr->next;
		free_red(ptr->red);
		m_freetab(ptr->cmds);
		free(ptr);
		ptr = tmp;
	}
	if (option)
		m_putstr("error: failed during allocation\n", 2);
	return (NULL);
}

static t_parse	*new_node(t_red *red, char **cmd)
{
	int		cmd_size;
	t_parse	*new_node;

	cmd_size = 0;
	new_node = malloc(sizeof(t_parse));
	if (!new_node)
		return (NULL);
	while (cmd && cmd[cmd_size])
		cmd_size++;
	new_node->pipe_type = 0;
	new_node->list_size = cmd_size;
	new_node->red = red;
	new_node->cmds = cmd;
	new_node->next = NULL;
	return (new_node);
}

t_parse	*add_parse(t_parse *begin, t_red *red, char **cmd)
{
	t_parse	*new;
	t_parse	*act;

	act = begin;
	if (!begin)
		return (new_node(red, cmd));
	while (act->next)
		act = act->next;
	new = new_node(red, cmd);
	if (!new)
		return (free_list(begin, 1));
	act->next = new;
	return (begin);
}

void	assign_pipe_type(t_parse *parse)
{
	if (!parse || !parse->next) //!parse->pipe_type)
		return ;
	parse->pipe_type = 1;
	parse = parse->next;
	while (parse)
	{
		if (!parse->next)
			parse->pipe_type = 3;
		else
			parse->pipe_type = 2;
		parse = parse->next;
	}
}
