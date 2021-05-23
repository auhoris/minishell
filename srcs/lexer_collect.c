#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/token.h"
#include "includes/utils.h"

t_token	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	lexer_advance(lexer);
	while ((!ft_inset(SPECIAL, lexer->c)
			&& lexer->c != SPACE) && lexer->c != '\0')
	{
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c == SPACE)
		return (init_token(TOKEN_DOLLAR, str, TRUE));
	return (init_token(TOKEN_DOLLAR, str, FALSE));
}

t_token	*lexer_collect_id(t_lexer *lexer)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	while ((!ft_inset(SPECIAL, lexer->c)
			&& lexer->c != SPACE) && lexer->c != '\0')
	{
		if (lexer->c == '=')
			break ;
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	/* Сделано, чтобы различать ситуации,
	когда после ID есть пробел или нет,
	т.к. в bash можно написать echo asd$PATH */
	if (lexer->c == SPACE)
		return (init_token(TOKEN_ID, str, TRUE));
	return (init_token(TOKEN_ID, str, FALSE));
}

t_token	*lexer_collect_bslash(t_lexer *lexer)
{
	char	*str;
	int		spec_id;

	lexer_advance(lexer);
	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	spec_id = 0;
	/* Забирает всё, что идёт после '\' до тех
	пор пока не встретит второй раз спец символ или пробел */
	while (lexer->c != '\0')
	{
		if (spec_id > 0 && ft_inset(SPECIAL, lexer->c))
			return (init_token(TOKEN_BSLASH, str, FALSE));
		else if (spec_id > 0 && lexer->c == SPACE)
			return (init_token(TOKEN_BSLASH, str, TRUE));
		str = connect_str(str, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
		spec_id++;
	}
	return (init_token(TOKEN_BSLASH, str, FALSE));
}

t_token	*lexer_collect_squote(t_lexer *lexer)
{
	char	*string;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\'' && lexer->c != '\0')
	{
		string = connect_str(string, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c != '\'')
	{
		return (init_token(BAD_TOKEN, string, FALSE));
	}
	lexer_advance(lexer);
	if (lexer->c == SPACE)
		return (init_token(TOKEN_SQUOTE, string, TRUE));
	return (init_token(TOKEN_SQUOTE, string, FALSE));
}

t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*string;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\"' && lexer->c != '\0')
	{
		if (lexer->c == '\\')
		{
			string = connect_str(string, lexer_chtostr(lexer->c));
			lexer_advance(lexer);
		}
		string = connect_str(string, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	if (lexer->c != '\"')
		return (init_token(BAD_TOKEN, string, FALSE));
	lexer_advance(lexer);
	if (lexer->c == SPACE)
		return (init_token(TOKEN_SQUOTE, string, TRUE));
	return (init_token(TOKEN_DQUOTE, string, FALSE));
}
/*
t_token	*lexer_collect_equals(t_lexer *lexer)
{
	if (lexer_peek(lexer, 1) == SPACE || lexer_peek(lexer, -1) == SPACE)
	{
		lexer_advance(lexer);
		return (init_token(BAD_TOKEN, "="));
	}
	lexer_advance(lexer);
	return (init_token(TOKEN_EQUALS, "="));
} */

/* t_token		*lexer_collect_flags(t_lexer *lexer)
{
	char	*value;

	value = ft_strdup("");
	if (value == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != SPACE && lexer->c != '\0')
	{
		value = connect_str(value, lexer_chtostr(lexer->c));
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_FLAG, value));
} */
