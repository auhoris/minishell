#include "includes/errors.h"
#include "includes/minishell.h"
#include "includes/parser.h"
#include "includes/token.h"
#include <stdio.h>
#include <unistd.h>

int	handle_error(t_parser *parser)
{
	destroy_token(parser->prev_token);
	return (ERROR);
}

int	parser_next_token(t_parser *parser)
{
	static int	i;
	int			type;
	int			prev_type;

	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	if (parser->cur_tok == NULL)
		return (handle_error(parser));
	prev_type = parser->prev_token->e_type;
	type = parser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
		i = 0;
	if (type == BAD_TOKEN)
	{
		printf("\n\n!!!ALERT\n\n");
		return (handle_error(parser));
	}
	else if (prev_type == TOKEN_PIPE && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		return (handle_error(parser));
	}
	else if ((prev_type == TOKEN_SEMI || prev_type == TOKEN_PIPE) && i == 0)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		return (handle_error(parser));
	}
	else if ((prev_type == TOKEN_LESS
			|| prev_type == TOKEN_MORE
			|| prev_type == TOKEN_DMORE) && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (handle_error(parser));
	}
	i++;
	destroy_token(parser->prev_token);
	return (type);
}
