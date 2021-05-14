#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"
# include "token.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
}		t_parser;

t_parser	*init_parser(t_lexer *lexer);
t_parser	*parser_expect(t_parser *parser, int type);

#endif /* ifndef PARSER_H */
