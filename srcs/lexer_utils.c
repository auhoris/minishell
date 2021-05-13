#include "includes/lexer.h"

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
	lexer->current++;
	lexer->c = lexer->content[lexer->current];
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char		lexer_peek(t_lexer *lexer, int offset)
{
	if (lexer->current + offset < lexer->length)
		return (lexer->content[lexer->current + offset]);
	return (lexer->content[lexer->length - 1]);
}

size_t	lexer_count_quotes(char *str, char qt)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != ';' || str[i] != '|')
	{
		if (str[i] == qt)
			cnt++;
		i++;
	}
	return (cnt);
}
