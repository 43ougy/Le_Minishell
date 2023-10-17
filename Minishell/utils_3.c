/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abougy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:06:45 by abougy            #+#    #+#             */
/*   Updated: 2023/10/17 12:08:59 by abougy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

int	_is_char(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	_is_quotes(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	_is_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (0);
	return (1);
}

int	_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	_is_limiter(char c)
{
	if (c == '!' || c == '@' || c == '#' || c == '%'
		|| c == '^' || c == '&' || c == '*'
		|| c == '(' || c == ')' || c == '-'
		|| c == '_' || c == '+' || c == '=')
		return (1);
	return (0);
}
