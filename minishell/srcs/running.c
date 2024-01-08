/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:29:18 by abougy            #+#    #+#             */
/*   Updated: 2024/01/02 15:29:19 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool		parse_check(char *prompt, t_shell *data);
t_parse		*parse(t_shell *data);
void		execlist(t_shell *data);
/* ----------------------------------------- */

/* ================== to remove ================== */
/*void	print_red(char **red, int i)
{
	printf("red[%d]=", i);
	if (!red)
		printf("NULL");
	else
		for (int j = 0; red && red[j]; j++)
			printf("[%s] ", red[j]);
	printf("\n");
}

void	print_list(t_parse *ll)
{
	int	idx = 0;
	while (ll)
	{
		printf("cmd %d:\n", idx++);
		for (int i = 0; ll->cmds && ll->cmds[i]; i++)
			printf("[%s] ", ll->cmds[i]);
		printf("\n");
		print_red(ll->red->input1, 1);
		print_red(ll->red->input2, 2);
		print_red(ll->red->output1, 3);
		print_red(ll->red->output2, 4);
		ll = ll->next;
	}
}*/
/* =============================================== */

// check for readline() errors
static int	prompt_check(t_shell *data)
{
	if (isatty(0) && isatty(2))
	{
		data->prompt = readline("\x1B[1m\x1B[41mHell$\x1B[0m ");
		if (!data->prompt)
		{
			m_putstr("exit\n", 1);
			m_freetab(data->env);
			exit(0);
		}
	}
	if (!data->prompt[0])
		return (1);
	return (0);
}

// remove space before redirection { > or < }
static void	parse_prep(t_shell *data)
{
	int		i;
	int		idx;
	int		red;
	char	ret[PROMPT_MAX_SZ];

	i = -1;
	idx = 0;
	red = 0;
	m_bzero(&ret, PROMPT_MAX_SZ);
	while (data->prompt && data->prompt[++i])
	{
		if (data->prompt[i] == '<' || data->prompt[i] == '>')
			red = 1;
		else if (data->prompt[i] != ' ' && data->prompt[i] != '<'
			&& data->prompt[i] != '>')
			red = 0;
		if (m_iswhitespace(data->prompt[i]) && red)
			continue ;
		ret[idx++] = data->prompt[i];
	}
	free(data->prompt);
	data->prompt = m_strdup(ret);
}

/* 
	The running() function will call all different functions 
	needed for the parsing and the execution
*/
bool	running(t_shell *data)
{
	t_parse	*cmds;

	if (prompt_check(data))
		return (false);
	add_history(data->prompt);
	if (!parse_check(data->prompt, data))
		return (false);
	parse_prep(data);
	if (!data->prompt)
		return (true);
	cmds = parse(data);
	assign_pipe_type(cmds);
	/* ============== */
	//print_list(cmds);
	/* ============== */
	data->begin_list = cmds;
	execlist(data);
	free_list(cmds, 0);
	free(data->prompt);
	data->begin_list = NULL;
	return (false);
}
