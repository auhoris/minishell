/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:14:23 by auhoris           #+#    #+#             */
/*   Updated: 2020/10/31 17:02:20 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p_s1;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	p_s1 = malloc(sizeof(*p_s1) * (len + 1));
	if (p_s1 == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		p_s1[i] = s1[i];
		i++;
	}
	p_s1[i] = '\0';
	return (p_s1);
}
