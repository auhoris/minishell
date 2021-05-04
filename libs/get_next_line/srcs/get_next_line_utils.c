/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:38:10 by auhoris           #+#    #+#             */
/*   Updated: 2021/05/04 18:38:54 by vlados_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/get_next_line.h"

char	*ft_nlpos(char *str)
{
	int		i;
	char	*res;

	if (str == NULL)
		return (NULL);
	i = 0;
	res = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			res = &str[i];
			return (res);
		}
		i++;
	}
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	length;

	if (s == 0)
		return (0);
	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

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

char	*ft_strdup(const char *s1)
{
	char	*p_s1;
	size_t	len;
	size_t	i;

	if (s1 == NULL)
		return (NULL);
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
