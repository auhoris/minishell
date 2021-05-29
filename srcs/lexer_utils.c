#include "includes/lexer.h"
#include "includes/minishell.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

char	*lexer_chtostr(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(*str));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->current < lexer->length)
	{
		lexer->current++;
		lexer->c = lexer->content[lexer->current];
	}
}

char	lexer_peek(t_lexer *lexer, int offset)
{
	if (lexer->current + offset < lexer->length)
		return (lexer->content[lexer->current + offset]);
	return ('\0');
}

int	seek_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*connect_str(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	if (s1 == NULL)
		return (NULL);
	free(s2);
	s2 = NULL;
	return (s1);
}
