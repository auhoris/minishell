#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/token.h"
#include "includes/utils.h"

#define MSG "minishell: syntax error near unexpected token "
#define EOF_MSG "minishell: syntax error: unexpected end of file"
#define TM TOKEN_MORE
#define TL TOKEN_LESS
#define TD TOKEN_DMORE

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

int	err_msg(t_parser *parser, char *msg, char *token, int code)
{
	handle_error_msg(msg, token);
	return (handle_error(parser, code));
}

int	handle_parser(t_parser *parser, int ct, int pt)
{
	if (ct == TOKEN_SEMI && pt == TOKEN_PIPE)
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	else if (pt == TOKEN_PIPE && ct == TOKEN_EOF)
		return (err_msg(parser, EOF_MSG, "", ERROR_PARSER));
	else if ((pt == TL || pt == TM || pt == TD) && ct == TOKEN_EOF)
		return (err_msg(parser, MSG, "newline", ERROR_PARSER));
	else if ((pt == TL || pt == TM || pt == TD) && ct == TOKEN_SEMI)
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	else if ((pt == TL || pt == TM || pt == TD) && ct == TOKEN_PIPE)
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	else if ((ct == TOKEN_MORE && (pt == TOKEN_MORE || pt == TOKEN_LESS)))
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	else if ((ct == TOKEN_LESS && (pt == TOKEN_MORE || pt == TOKEN_LESS)))
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	return (OK);
}

int	parser_next_token(t_parser *parser)
{
	int			ct;
	int			pt;
	int			err;

	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	if (parser->cur_tok == NULL)
		return (handle_error(parser, ERROR_MALLOC));
	if (parser->cur_tok->e_type == BAD_TOKEN)
		return (handle_error(parser, ERROR_PARSER));
	pt = parser->prev_token->e_type;
	ct = parser->cur_tok->e_type;
	if (ct == TOKEN_PIPE && pt == TOKEN_PIPE)
		return (err_msg(parser, MSG, parser->cur_tok->value, ERROR_PARSER));
	if (ct == TOKEN_SEMI && pt == TOKEN_SEMI)
		return (err_msg(parser, MSG, parser->prev_token->value, ERROR_PARSER));
	err = handle_parser(parser, ct, pt);
	if (err != OK)
		return (err);
	destroy_token(parser->prev_token);
	return (ct);
}
// return (err_msg(parser, MSG, parser->prev_token->value, ERROR_PARSER));
/* else if (type == TOKEN_SEMI && prev_type == TOKEN_SEMI)
{
	printf("here\n");
	return (error_with_msg(parser, MSG,
			parser->prev_token->value, ERROR_PARSER));
} */
