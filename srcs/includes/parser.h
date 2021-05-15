#ifndef PARSER_H
# define PARSER_H

#include "commands.h"
# include "lexer.h"
# include "token.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*current_token;
}			t_parser;

t_parser	*init_parser(t_lexer *lexer);
void		*parser_expect(t_parser *parser, int type);
t_cmd_table	*parser_parse_commands(t_parser *parser);
t_cmd_table	*parser_parse_command(t_parser *parser);


#endif /* ifndef PARSER_H */
