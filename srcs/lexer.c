#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/token.h"
#include <stdlib.h>

t_lexer	*init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(*lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->length = ft_strlen(content);
	lexer->content = ft_strdup(content);
	if (lexer->content == NULL)
	{
		free(lexer);
		return (NULL);
	}
	lexer->current = 0;
	lexer->c = lexer->content[lexer->current];
	lexer->flag = FALSE;
	return (lexer);
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

t_token	*lexer_special_tokens(t_lexer *lexer)
{
	if (lexer->c == ';')
		return (lexer_advance_with(lexer,
				init_token(TOKEN_SEMI, lexer_chtostr(lexer->c), FALSE)));
	else if (lexer->c == '<')
		return (lexer_advance_with(lexer,
				init_token(TOKEN_LESS, lexer_chtostr(lexer->c), FALSE)));
	else if (lexer->c == '>')
	{
		if (lexer_peek(lexer, 1) == '>')
			return (lexer_advance_with(lexer, lexer_advance_with(lexer,
						init_token(TOKEN_DMORE, ft_strdup(">>"), FALSE))));
		return (lexer_advance_with(lexer,
				init_token(TOKEN_MORE, lexer_chtostr(lexer->c), FALSE)));
	}
	else if (lexer->c == '=')
	{
		if (lexer_peek(lexer, -1) == ' ' || lexer_peek(lexer, 1) == ' ')
			return (lexer_advance_with(lexer,
					init_token(BAD_TOKEN, lexer_chtostr(lexer->c), FALSE)));
		return (lexer_advance_with(lexer,
				init_token(TOKEN_EQUALS, lexer_chtostr(lexer->c), FALSE)));
	}
	return (lexer_advance_with(lexer,
			init_token(TOKEN_PIPE, lexer_chtostr(lexer->c), FALSE)));
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0' && lexer->c != '\0')
	{
		if (lexer->flag == FALSE)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '\'')
			return (lexer_collect_squote(lexer));
		if (ft_isalnum(lexer->c) || ft_inset(OTHER, lexer->c))
			return (lexer_collect_id(lexer));
		if (lexer->c == '$')
			return (lexer_collect_dollar(lexer));
		if (lexer->c == '"' || lexer->flag == TRUE)
		{
			return (lexer_collect_dquote(lexer));
		}
		if (lexer->c == '\\')
			return (lexer_collect_bslash(lexer));
		if (ft_inset(";<|>=", lexer->c))
			return (lexer_special_tokens(lexer));
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_EOF, ft_strdup(""), FALSE));
}
