#include "includes/lexer.h"
#include "includes/utils.h"

t_token	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	lexer_advance(lexer);
	while ((!ft_inset(SPECIAL, lexer->c) && lexer->c != SPACE) && lexer->c != '\0')
	{
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c == SPACE)
		str = connect_str(str, lexer_chtostr(lexer->c));
	return (init_token(TOKEN_DOLLAR, str));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	while ((!ft_inset(SPECIAL, lexer->c) && lexer->c != SPACE) && lexer->c != '\0')
	{
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	//	Сделано, чтобы различать ситуации, когда после ID есть пробел или нет, т.к. в bash можно написать echo asd$PATH
	if (lexer->c == SPACE && ft_inset(SPECIAL, lexer_peek(lexer, 1)))
		str = connect_str(str, lexer_chtostr(lexer->c));
	return (init_token(TOKEN_ID, str));
}

t_token		*lexer_collect_bslash(t_lexer *lexer)
{
	char	*str;
	int		spec_id;

	lexer_advance(lexer);
	if ((str = ft_strdup("")) == NULL)
		return (NULL);
	spec_id = 0;
	//	Забирает всё, что идёт после '\' до тех пор пока не встретит второй раз спец символ или пробел
	while (lexer->c != '\0')
	{
		if (spec_id > 0 && (ft_inset(SPECIAL, lexer->c) || lexer->c == SPACE))
			return (init_token(TOKEN_BSLASH, str));
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
		spec_id++;
	}
	return (init_token(TOKEN_BSLASH, str));
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*string;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->current < lexer->length)
	{
		string = connect_str(string, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c != '\'')
		return (init_token(TOKEN_NULL, "\0"));
	lexer_advance(lexer);
	return (init_token(TOKEN_SQUOTE, string));
}

t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*string;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\"' && lexer->current < lexer->length)
	{
		string = connect_str(string, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c != '\"')
		return (init_token(TOKEN_NULL, string));
	lexer_advance(lexer);
	return (init_token(TOKEN_DQUOTE, string));
}
