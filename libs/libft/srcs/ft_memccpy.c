/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:03:44 by auhoris           #+#    #+#             */
/*   Updated: 2020/10/31 17:43:49 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned const char	*ptr_src;
	char				*ret_ptr;

	i = 0;
	ptr_src = (unsigned const char *)src;
	ret_ptr = (char *)dst;
	while (i < n)
	{
		if (ptr_src[i] == (unsigned char)c)
		{
			n = i + 1;
			ft_memcpy(dst, src, n);
			return (++ret_ptr);
		}
		ret_ptr++;
		i++;
	}
	ft_memcpy(dst, src, n);
	return (0);
}
