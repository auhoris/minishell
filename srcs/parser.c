#include "includes/parser.h"
#include "includes/lexer.h"
#include <stdlib.h>

t_parser	*parser_expect(t_parser *parser, int type)
{
	if ((int)parser->current_token->e_type != type)
	{
		printf("[Parser]: Unexpected token '%d', with value '%s'\n",
				parser->current_token->e_type, parser->current_token->value);
		exit(1);
	}
	parser->current_token = lexer_get_next_token(parser->lexer);
	return (parser);
}

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	return (parser);
}

void	parser_proceed(t_parser *parser)
{
	parser_expect(parser, TOKEN_CMD);
}
