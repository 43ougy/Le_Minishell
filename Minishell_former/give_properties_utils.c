/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_properties_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:21:30 by abougy            #+#    #+#             */
/*   Updated: 2023/12/04 13:04:25 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

void	_infile_chevron(t_prompt *data, int i)
{
	data->cmde[i + 1].infile = 1;
	data->infile = data->cmde[i + 1].cmd[0];
	data->cmde[i + 1].path = ft_strdup("infile");
}

void	_outfile_chevron(t_prompt *data, int i)
{
	data->cmde[i + 1].outfile = 1;
	data->outfile = data->cmde[i + 1].cmd[0];
	data->cmde[i + 1].path = ft_strdup("outfile");
}

void	_chevron_file(t_prompt *data, int i, int j, char *input)
{
	int	n;

	n = -1;
	if (input[j] == '<' && input[j + 1] != '<')
		_infile_chevron(data, i);
	else if (input[j] == '<' && input[j + 1] == '<')
	{
		_infile_chevron(data, i);
		data->heredoc = 1;
	}
	else if (input[j] == '>' && input[j + 1] != '>')
		_outfile_chevron(data, i);
	else if (input[j] == '>' && input[j + 1] == '>')
	{
		_outfile_chevron(data, i);
		data->append = 1;
	}
	else
		while (++n < data->cmde[i].n_inarg)
			if (open(data->cmde[i].cmd[n], O_RDONLY) != -1)
				data->cmde[i].file = 1;
}
