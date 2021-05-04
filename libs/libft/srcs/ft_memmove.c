/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:48:02 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/03 21:04:19 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p_dst;
	unsigned const char	*p_src;
	size_t				i;

	if (dst == 0 && src == 0)
		return (0);
	p_dst = (unsigned char *)dst;
	p_src = (unsigned const char *)src;
	i = 0;
	if (p_dst < p_src)
	{
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			p_dst[len] = p_src[len];
	}
	return (dst);
}
