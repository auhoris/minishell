/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:40:40 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/05 19:55:15 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (needle == 0 || *needle == '\0')
		return ((char *)haystack);
	k = 0;
	while ((i = k) < len && haystack[k] != '\0')
	{
		j = 0;
		while (i < len && haystack[i] != '\0')
		{
			if (haystack[i] == needle[j])
			{
				j++;
				if (j == ft_strlen(needle))
					return ((char *)&haystack[k]);
			}
			else
				break ;
			i++;
		}
		k++;
	}
	return (0);
}
