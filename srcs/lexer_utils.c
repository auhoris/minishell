#include "includes/errors.h"
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

int	lexer_advance(t_lexer *lexer)
{
	if (lexer->c && lexer->current < lexer->length)
	{
		lexer->current++;
		lexer->c = lexer->content[lexer->current];
		return (OK);
	}
	return (ERROR);
}

char	lexer_peek(t_lexer *lexer, int offset)
{
	if (lexer->current + offset < lexer->length)
		return (lexer->content[lexer->current + offset]);
	return ('\0');
}
