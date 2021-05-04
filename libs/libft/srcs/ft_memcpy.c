/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:21:26 by auhoris           #+#    #+#             */
/*   Updated: 2020/10/31 17:35:29 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;

	if (dst == 0 && src == 0)
		return (0);
	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	while (n-- > 0)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}
