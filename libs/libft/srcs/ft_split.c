/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auhoris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 17:58:36 by auhoris           #+#    #+#             */
/*   Updated: 2020/11/04 21:08:07 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_amount(char const *s, char c)
{
	int		i;
	int		cnt;
	int		f;

	i = 0;
	cnt = 0;
	f = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && f != 1)
		{
			f = 1;
			cnt++;
		}
		else if (s[i] == c && f == 1)
			f = 0;
		i++;
	}
	return (cnt);
}

static char	*create_word(char **wrd_arr, int words, char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (!(word = malloc(sizeof(char) * (i + 1))))
	{
		while (words-- > 0)
			free(wrd_arr[words]);
		free(wrd_arr);
		return (0);
	}
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_split(char const *s, char c)
{
	char	**wrd_arr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (!(wrd_arr = malloc(sizeof(char **) * (word_amount(s, c) + 1))))
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(wrd_arr[i] = create_word(wrd_arr, i, s, c)))
				return (0);
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	wrd_arr[i] = 0;
	return (wrd_arr);
}
