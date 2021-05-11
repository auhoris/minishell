#include "includes/lexer.h"

t_token	*lexer_collect_dollar(t_lexer *lexer)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (ft_isalnum(lexer->c) && lexer->current < lexer->length)
	{
		tmp = str;
		str = ft_strjoin(str, lexer_chtostr(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_DOLLAR, str));
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
	if (lexer->c != '\'')
		return (init_token(TOKEN_NULL, "\0"));
	lexer_advance(lexer);
	return (init_token(TOKEN_SQUOTE, string));
}

t_token	*lexer_collect_dquote(t_lexer *lexer)
{
	char	*string;
	char	*tmp;

	string = ft_strdup("");
	if (string == NULL)
		return (NULL);
	lexer_advance(lexer);
	while (lexer->c != '\"' && lexer->current < lexer->length)
	{
		tmp = string;
		string = ft_strjoin(string, lexer_chtostr(lexer->c));
		free(tmp);
		lexer_advance(lexer);
	}
	if (lexer->c != '\"')
		return (init_token(TOKEN_NULL, "\0"));
	lexer_advance(lexer);
	return (init_token(TOKEN_DQUOTE, string));
}
