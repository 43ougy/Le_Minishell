/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_launcher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:18:29 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:18:31 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	_cmd_launcher(t_parse *parse, t_prompt *data)
{
	t_red	red;
	int		fd_in;
	int		*fd_out;
	int		status;

	fd_out = _out_red(red);
	fd_in = _in_red(red);
	status = _execute(parse, data, fd_in, fd_out[0]);
	return (status);
}
