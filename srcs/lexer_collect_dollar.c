#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/token.h"
#include "includes/utils.h"
#include <stdio.h>
#include <unistd.h>

#define SET "0123456789?="

static t_token	*handle_dollar_cases(t_lexer *lexer)
{
	if (ft_isdigit(lexer->c))
		return (lexer_advance_with(lexer,
				init_token(TOKEN_ID, ft_strdup(""), FALSE)));
	if (lexer->c == '?')
		return (lexer_advance_with(lexer,
				init_token(TOKEN_DOLLAR, ft_strdup("?"), FALSE)));
	if (lexer->c == ' ')
		return (init_token(TOKEN_ID, ft_strdup("$"), TRUE));
	return (init_token(TOKEN_ID, ft_strdup("$"), FALSE));
}

t_token	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	lexer_advance(lexer);
	if (ft_inset(SET, lexer->c) || lexer->c == '\0')
	{
		free(str);
		return (handle_dollar_cases(lexer));
	}
	while ((!ft_inset(SPECIAL, lexer->c)
			&& lexer->c != SPACE) && lexer->c != '\0')
	{
		if (lexer->c == '=')
			break ;
		str = connect_str(str, lexer_chtostr(lexer->c));
		if (str == NULL)
			return (NULL);
		lexer_advance(lexer);
	}
	if (lexer->c == SPACE && !lexer->flag)
		return (init_token(TOKEN_DOLLAR, str, TRUE));
	return (init_token(TOKEN_DOLLAR, str, FALSE));
}
	/* if (ft_isdigit(lexer->c))
	{
		free(str);
		return (lexer_advance_with(lexer,
				init_token(TOKEN_ID, ft_strdup(""), FALSE)));
	}
	if (lexer->c == '?')
	{
		free(str);
		return (lexer_advance_with(lexer,
				init_token(TOKEN_DOLLAR, ft_strdup("?"), FALSE)));
	} */
