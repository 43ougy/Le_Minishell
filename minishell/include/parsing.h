#ifndef PARSING_H
# define PARSING_H

#include "ra_shell.h"

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

// linked_list.c
t_parse		*new_node(t_red *red, char **cmd);
void		*free_list(t_parse *ptr, int option);
t_parse		*give_at(t_parse *begin, int pos);
t_parse		*add_parse(t_parse *begin, t_red *red, char **cmd);





/* ================== PLAN ================== */

// before:
// 	->	prompt_verif() for the quote

// extract_parse(); // 1

// 		extract_list(); // 2 -> return (list + t_red)

// 			char *extract_token(...);
// 			char *modified_token(...);
// 			int	add_token(t_token *list, char *token, bool replace);

// 		int	add_list(t_parse *parse, t_token *list, t_red *red);

#endif