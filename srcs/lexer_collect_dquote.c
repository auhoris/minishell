#include "includes/token.h"
#include "includes/lexer.h"
#include "includes/utils.h"

// Не понимаю зачем это нужно
/* static int	handle_checking(t_lexer *lexer)
{
	if (lexer->c == '\\' && lexer_peek(lexer, 1) != '\''
		&& lexer_peek(lexer, 1) != ';' && lexer_peek(lexer, 1) != '|'
		&& ft_inset(SPECIAL, lexer_peek(lexer, 1)))
	{
		printf("here\n");
		return (1);
	}
	return (0);
} */

static t_token	*handle_dollar_state(t_lexer *lexer, char *string)
{
	lexer->flag = TRUE;
	return (init_token(TOKEN_DQUOTE, string, FALSE));
}

/* else if (handle_checking(lexer))
	lexer_advance(lexer); */
t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*string;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	if (lexer->flag == FALSE)
		lexer_advance(lexer);
	lexer->flag = FALSE;
	if (seek_quote(&lexer->content[lexer->current]) == FALSE)
		return (lexer_errors_handler(init_token(TOKEN_DQUOTE, string, FALSE)));
	while (lexer->c != '\"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
			return (handle_dollar_state(lexer, string));
		string = connect_str(string, lexer_chtostr(lexer->c));
		if (string == NULL)
			return (NULL);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	if (lexer->c == SPACE)
		return (init_token(TOKEN_DQUOTE, string, TRUE));
	return (init_token(TOKEN_DQUOTE, string, FALSE));
}
