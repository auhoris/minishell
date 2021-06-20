#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/token.h"
#include "includes/utils.h"
#include <stdio.h>
#include <unistd.h>

t_token	*lexer_errors_handler(t_token *token)
{
	if (token->e_type == TOKEN_SQUOTE)
	{
		handle_error_msg(
			"minishell: unexpected EOF while looking for matching ", "'");
		ft_putstr_fd(
			"minishell: syntax error: unexpected end of file\n", STDERR_FILENO);
	}
	else if (token->e_type == TOKEN_DQUOTE)
	{
		handle_error_msg(
			"minishell: unexpected EOF while looking for matching ", "\"");
		ft_putstr_fd(
			"minishell: syntax error: unexpected end of file\n", STDERR_FILENO);
	}
	else
	{
		handle_error_msg(
			"minishell: syntax error near unexpected token ", token->value);
	}
	return (init_token(BAD_TOKEN, ft_strdup(""), FALSE));
}

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
		if (str == NULL)
			return (NULL);
		if (ft_isdigit(lexer->c))
		{
			lexer_advance(lexer);
			break ;
		}
		lexer_advance(lexer);
	}
	if (lexer->c == SPACE && !lexer->flag)
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
		if (str == NULL)
			return (NULL);
		lexer_advance(lexer);
	}
	if (lexer->c == SPACE)
		return (init_token(TOKEN_ID, str, TRUE));
	return (init_token(TOKEN_ID, str, FALSE));
}

t_token	*lexer_collect_bslash(t_lexer *lexer)
{
	char	*str;
	int		spec_id;

	lexer_advance(lexer);
	if (lexer->c == '\0')
		return (lexer_errors_handler(init_token(TOKEN_BSLASH,
					ft_strdup(""), FALSE)));
	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	spec_id = 0;
	while (lexer->c != '\0')
	{
		if (spec_id > 0 && ft_inset(SPECIAL, lexer->c))
			return (init_token(TOKEN_BSLASH, str, FALSE));
		else if (spec_id > 0 && lexer->c == SPACE)
			return (init_token(TOKEN_BSLASH, str, TRUE));
		str = connect_str(str, lexer_chtostr(lexer->c));
		if (str == NULL)
			return (NULL);
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
		if (string == NULL)
			return (NULL);
		lexer_advance(lexer);
	}
	if (lexer->c != '\'')
		return (lexer_errors_handler(init_token(TOKEN_SQUOTE, string, FALSE)));
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
	if (lexer->flag == FALSE)
		lexer_advance(lexer);
	lexer->flag = FALSE;
	if (seek_quote(&lexer->content[lexer->current]) == FALSE)
		return (lexer_errors_handler(init_token(TOKEN_DQUOTE, string, FALSE)));
	while (lexer->c != '\"' && lexer->c != '\0')
	{
		if (lexer->c == '$')
		{
			lexer->flag = TRUE;
			return (init_token(TOKEN_DQUOTE, string, FALSE));
		}
		else if (lexer->c == '\\'
			&& lexer_peek(lexer, 1) != '\''
			&& lexer_peek(lexer, 1) != ';'
			&& lexer_peek(lexer, 1) != '|'
			&& ft_inset(SPECIAL, lexer_peek(lexer, 1)))
			lexer_advance(lexer);
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
