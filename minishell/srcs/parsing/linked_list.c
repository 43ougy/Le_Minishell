#include "ra_shell.h"

t_parse	*new_node(t_red *red, char **cmd)
{
	int		cmd_size;
	t_parse	*new_node;

	cmd_size = 0;
	new_node = _calloc(sizeof(t_parse));
	if (!new_node)
		return (NULL);
	while (cmd && cmd[cmd_size])
		cmd_size++;
	new_node->indice = pos;
	new_node->list_size = cmd_size;
	new_node->red = red;
	new_node->cmd = cmd;
	new_node->next = NULL;
}

void	*free_list(t_parse *ptr, int option)
{
	t_parse	*tmp;

	while (ptr)
	{
		tmp = ptr->next;
		free_red(ptr->red);
		_free_tab(ptr->cmds);
		free(ptr);
		ptr = tmp;
	}
	if (1 == option)
		write(2, "error: failed during allocation\n", 32);
	return (NULL);
}

// 0 -> first / -1 -> last / n -> n in the list
t_parse	*give_at(t_parse *begin, int pos)
{
	int	i;

	i = 0;
	while (begin && (-1 == pos || i < pos))
		begin = begin->next;
	return (begin);
}

t_parse	*add_parse(t_parse *begin, t_red *red, char **cmd)
{
	t_parse	*new;
	t_parse	*act;

	act = begin;
	if (!begin)
		return (new_node(red, cmd))
	while (act->next)
		act = act->next;
	new = new_node(red, cmd);
	if (!new_node)
		return (free_list(begin, 1));
	act->next = new;
	return (begin);
}