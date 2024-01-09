/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:37:50 by abougy            #+#    #+#             */
/*   Updated: 2024/01/09 13:37:51 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_all(t_shell *data, int *fd_out)
{
	free(fd_out);
	free(data->prompt);
	m_freetab(data->env);
	free_list(data->begin_list, 0);
}
