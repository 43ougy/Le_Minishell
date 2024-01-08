/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:17:54 by abougy            #+#    #+#             */
/*   Updated: 2023/12/07 10:17:56 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_pwd(void)
{
	char	location[1024];

	if (!getcwd(location, sizeof(location)))
	{
		perror("pwd");
		return (1);
	}
	write(1, location, m_strlen(location));
	write(1, "\n", 1);
	return (0);
}
