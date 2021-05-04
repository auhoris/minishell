/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:11:43 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/02 17:21:54 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void		ft_putnbr_fd(int n, int fd)
{
	int	sv_n;
	int	ten_pow;

	sv_n = n;
	ten_pow = 1;
	if (n < 0)
		ft_putchar_fd('-', fd);
	while ((sv_n /= 10) != 0)
		ten_pow *= 10;
	while (ten_pow != 0)
	{
		ft_putchar_fd('0' + ft_abs(n / ten_pow % 10), fd);
		n %= ten_pow;
		ten_pow /= 10;
	}
}
