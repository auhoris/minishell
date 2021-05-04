/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:23:11 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/03 21:06:46 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_res;
	int		k;
	int		i;

	if (s1 == 0 || s2 == 0)
		return (0);
	p_res = malloc(sizeof(*p_res) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (p_res == 0)
		return (0);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
		p_res[k++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		p_res[k++] = s2[i++];
	p_res[k] = '\0';
	return (p_res);
}
