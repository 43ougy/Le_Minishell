/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:16:38 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:16:40 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "ra_shell.h"

// between quotes, other quotes aren't interpret
// ec"ho" $"PA$PATHTH"test -> PAtest

/* ===================== struct ==================== */

typedef struct s_redirection
{
	char	**input1;
	char	**input2;
	char	**output1;
	char	**output2;
}	t_red;

typedef struct s_parse
{
	int				pipe_type; /* 0 -> first | 1 -> middle | 2 -> last */
	int				list_size;
	t_red			*red;
	char			**cmds;
	struct s_parse	*next;
}	t_parse;

/* ===================== protos ==================== */

// parsing.c
t_parse		*parse(t_prompt *data, char *ret_value);
char		**extract_cmd(t_prompt *data, int *pos, t_red **red);
bool		quote_check(char *prompt);

// linked_list.c
t_parse		*new_node(t_red *red, char **cmd);
void		*free_list(t_parse *ptr, int option);
t_parse		*give_at(t_parse *begin, int pos);
t_parse		*add_parse(t_parse *begin, t_red *red, char **cmd);

// token.c
char		*extract_token(char *prompt, int *pos);
char		*modified_token(char *token, t_red *red, int *status);

// token_ext.c
char		*add_str(char *src, char *str);
char		*add_char(char *src, char c);

#endif
