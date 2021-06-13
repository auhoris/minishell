#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/token.h"
#include "includes/utils.h"

#define MSG "\nminishell: syntax error near unexpected token "

t_parser	*init_parser(t_lexer *lexer, t_env_list *env)
{
	t_parser	*parser;

	if (lexer == NULL)
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->prev_token = NULL;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	if (parser->cur_tok == NULL)
	{
		free(parser);
		return (NULL);
	}
	parser->env = env;
	return (parser);
}

static int	handle_error(t_parser *parser, int code)
{
	destroy_token(parser->prev_token);
	return (code);
}

int	error_with_msg(t_parser *parser, char *msg, char *token, int code)
{
	handle_error_msg(msg, token);
	return (handle_error(parser, code));
}

// Разобраться с кейсом echo ; ; / echo | | и тому подобное
int	parser_next_token(t_parser *parser)
{
	static int	i;
	int			type;
	int			prev_type;

	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	if (parser->cur_tok == NULL)
		return (handle_error(parser, ERROR_MALLOC));
	if (parser->cur_tok->e_type == BAD_TOKEN)
		return (handle_error(parser, ERROR_PARSER));
	prev_type = parser->prev_token->e_type;
	type = parser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
		i = 0;
	else if (prev_type == TOKEN_PIPE && type == TOKEN_EOF)
		return (error_with_msg(parser, MSG, parser->prev_token->value, ERROR_PARSER));
	else if (type == TOKEN_SEMI && prev_type == TOKEN_PIPE)
		return (error_with_msg(parser, MSG, parser->prev_token->value, ERROR_PARSER));
	else if (type == TOKEN_SEMI && prev_type == TOKEN_SEMI)
		return (error_with_msg(parser, MSG, parser->prev_token->value, ERROR_PARSER));
	else if ((prev_type == TOKEN_LESS
			|| prev_type == TOKEN_MORE
			|| prev_type == TOKEN_DMORE) && type == TOKEN_EOF)
		return (error_with_msg(parser, MSG, "newline", ERROR_PARSER));
	i++;
	destroy_token(parser->prev_token);
	return (type);
}
