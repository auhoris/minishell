/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:32:47 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/05 18:08:08 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*p_res;
	int		len;
	int		i;
	int		k;

	if (s1 == 0 || set == 0)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	while (in_set(set, s1[i]))
		i++;
	while (in_set(set, s1[len - 1]))
		len--;
	if (len < i)
		return (ft_strdup(""));
	if (!(p_res = malloc(sizeof(*p_res) * (len - i + 1))))
		return (0);
	k = 0;
	while (i < len)
		p_res[k++] = s1[i++];
	p_res[k] = '\0';
	return (p_res);
}
