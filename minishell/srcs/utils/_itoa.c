/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _itoa.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbeaufil <nbeaufil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:27:42 by abougy            #+#    #+#             */
/*   Updated: 2023/12/04 14:18:50 by nbeaufil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ra_shell.h"

static void	_reverse_tab(char *tab, size_t size)
{
	size_t	i;
	char	tmp;

	i = 0;
	while (i < size / 2)
	{
		tmp = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = tmp;
		i++;
	}
}

char	*_itoa(int n)
{
	int			i;
	int			sign;
	char		buff[33];
	long int	nb;

	i = 0;
	sign = 0;
	nb = (long int)n;
	if (n == 0)
		return (_strdup("0"));
	if (nb < 0)
	{
		sign = 1;
		nb = -nb;
	}
	while (nb)
	{
		buff[i++] = (nb % 10) + 48;
		nb /= 10;
	}
	if (sign)
		buff[i++] = '-';
	buff[i] = 0;
	_reverse_tab(buff, _strlen(buff));
	return (_strdup(buff));
}
