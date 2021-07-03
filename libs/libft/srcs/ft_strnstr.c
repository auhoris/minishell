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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	first;

	i = 0;
	if (little[i] == '\0' || !little)
		return ((char *) big);
	while (big[i])
	{
		if (big[i] == little[0])
		{
			first = i;
			j = 0;
			while (big[i] == little[j] && little[j] && big[i] && i < len)
			{
				i++;
				j++;
			}
			if (j == ft_strlen(little))
				return ((char *)(big + first));
			i = first;
		}
		i++;
	}
	return (NULL);
}
