/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:09:40 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/10 14:30:16 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_symbols(char c)
{
	char	*symbols;
	int		i;

	symbols = "\r\n\f\t\v ";
	i = 0;
	while (i < 6)
	{
		if (c == symbols[i])
			return (1);
		i++;
	}
	return (0);
}

int			ft_atoi(const char *str)
{
	int		nbr;
	int		i;
	int		minus;

	i = 0;
	minus = 1;
	nbr = 0;
	while (in_symbols(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	return (minus * nbr);
}
