#include "includes/lexer.h"
#include "includes/token.h"

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

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->c != '\0')
	{
		if (lexer->c == ' ')
			lexer_skip_whitespace(lexer);
		if (lexer->c == '\'')
			return (lexer_collect_squote(lexer));
		if (lexer->c == '"')
			return (lexer_collect_dquote(lexer));
		if (ft_isalnum(lexer->c) || ft_inset(OTHER, lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '-')
			return (lexer_collect_flags(lexer));
		if (lexer->c == '$')
		{
			if (ft_isalnum(lexer_peek(lexer, 1)))
				return (lexer_collect_dollar(lexer));
			return (lexer_advance_with(lexer,
					init_token(TOKEN_DOLLAR, lexer_chtostr(lexer->c))));
		}
		/* if (lexer->c == '=')
			return (lexer_collect_equals(lexer)); */
		if (lexer->c == '\\')
			return (lexer_collect_bslash(lexer));
		else if (lexer->c == ';')
			return (lexer_advance_with(lexer,
					init_token(TOKEN_SEMI, lexer_chtostr(lexer->c))));
		else if (lexer->c == '<')
			return (lexer_advance_with(lexer,
					init_token(TOKEN_LESS, lexer_chtostr(lexer->c))));
		else if (lexer->c == '>')
		{
			if (lexer_peek(lexer, 1) == '>')
				return (lexer_advance_with(lexer,
						lexer_advance_with(lexer,
							init_token(TOKEN_DMORE, ft_strdup(">>")))));
			return (lexer_advance_with(lexer,
					init_token(TOKEN_MORE, lexer_chtostr(lexer->c))));
		}
		else if (lexer->c == '|')
			return (lexer_advance_with(lexer,
					init_token(TOKEN_PIPE, lexer_chtostr(lexer->c))));
		else if (lexer->c == '=')
		{
			if (lexer_peek(lexer, -1) == ' ' || lexer_peek(lexer, 1) == ' ')
				return (lexer_advance_with(lexer, init_token(BAD_TOKEN, lexer_chtostr(lexer->c))));
			return (lexer_advance_with(lexer, init_token(TOKEN_EQUALS, lexer_chtostr(lexer->c))));
		}
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_EOF, "\0"));
}
