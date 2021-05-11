#include "lexer.h"

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(*lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->length = ft_strlen(content);
	lexer->content = content;
	lexer->current = 0;
	lexer->c = lexer->content[lexer->current];
	return (lexer);
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

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->current < lexer->length)
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '\'')
			return (lexer_collect_squote(lexer));
		if (lexer->c == '"')
			return (lexer_collect_dquote(lexer));
		if (ft_isalnum(lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '$')
			return (lexer_collect_dollar(lexer));
		if (lexer->c == '\\')
			return (lexer_advance_with(lexer, init_token(TOKEN_BSLASH, lexer_chtostr(lexer->c))));
		else if (lexer->c == ';')
			return (lexer_advance_with(lexer, init_token(TOKEN_SEMICOLON, lexer_chtostr(lexer->c))));
		else if (lexer->c == '<')
			return (lexer_advance_with(lexer, init_token(TOKEN_LESS, lexer_chtostr(lexer->c))));
		else if (lexer->c == '>')
		{
			if (lexer_peek(lexer, 1) == '>')
				return (lexer_advance_with(lexer, lexer_advance_with(lexer, init_token(TOKEN_DMORE, ">>"))));
			return (lexer_advance_with(lexer, init_token(TOKEN_MORE, lexer_chtostr(lexer->c))));
		}
		else if (lexer->c == '|')
			return (lexer_advance_with(lexer, init_token(TOKEN_PIPE, lexer_chtostr(lexer->c))));
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_EOF, "\0"));
}

t_token	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	while (ft_isalnum(lexer->c) && lexer->current < lexer->length)
	{
		tmp = str;
		str = ft_strjoin(str, lexer_chtostr(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_DOLLAR, str));
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	while (ft_isalnum(lexer->c) && lexer->current < lexer->length)
	{
		tmp = str;
		str = ft_strjoin(str, lexer_chtostr(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_ID, str));
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*string;
	char	*tmp;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->current < lexer->length)
	{
		tmp = string;
		string = ft_strjoin(string, lexer_chtostr(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_SQUOTE, string));
}

t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*string;
	(void)lexer;
	(void)string;
	return (init_token(TOKEN_EOF, "\0"));
}

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

char		lexer_peek(t_lexer *lexer, int offset)
{
	if (lexer->current + offset < lexer->length)
		return (lexer->content[lexer->current + offset]);
	return (lexer->content[lexer->length - 1]);
}
