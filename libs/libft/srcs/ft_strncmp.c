/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:42:51 by auhoris           #+#    #+#             */
/*   Updated: 2020/10/31 18:08:43 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	cs1;
	unsigned char	cs2;

	if (n >= 2147483647)
		return (0);
	while (n-- > 0 && (*s1 != '\0' || *s2 != '\0'))
	{
		cs1 = (unsigned char)*s1++;
		cs2 = (unsigned char)*s2++;
		if (cs1 != cs2)
			return (cs1 - cs2);
	}
	return (0);
}
