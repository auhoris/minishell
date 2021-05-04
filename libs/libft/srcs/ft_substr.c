/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:00:00 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/05 20:00:21 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_sbs;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (0);
	if (!(p_sbs = malloc(sizeof(*p_sbs) * (ft_min(ft_strlen(s), len) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0' && len > 0)
	{
		if (i >= start)
		{
			p_sbs[j] = s[i];
			len--;
			j++;
		}
		i++;
	}
	p_sbs[j] = '\0';
	return (p_sbs);
}
