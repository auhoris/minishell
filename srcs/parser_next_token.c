#include "includes/minishell.h"
#include "includes/parser.h"
#include "includes/token.h"
#include <stdio.h>

int	parser_next_token(t_parser *parser)
{
	static int	i;
	int			type;
	int			prev_type;

	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	prev_type = parser->prev_token->e_type;
	type = parser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
		i = 0;
	if (prev_type == BAD_TOKEN && type == TOKEN_EOF)
	{
		printf("minishell: unexpected EOF while looking for matching '\"'\n");
		printf("minishell: syntax error: unexpected end of file\n");
		exit(1);
	}
	else if (prev_type == BAD_TOKEN)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if (prev_type == TOKEN_PIPE && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if (type == TOKEN_SEMI && prev_type == TOKEN_SEMI)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if ((prev_type == TOKEN_SEMI || prev_type == TOKEN_PIPE) && i == 0)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if ((prev_type == TOKEN_LESS
			|| prev_type == TOKEN_MORE
			|| prev_type == TOKEN_DMORE) && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		exit(1);
	}
	i++;
	destroy_token(parser->prev_token);
	return (type);
}
