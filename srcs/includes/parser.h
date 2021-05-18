#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "token.h"
# include "ast.h"

typedef struct s_parser
{
	t_lexer	*lexer;
	t_token	*prev_token;
	t_token	*current_token;
}			t_parser;

t_parser	*init_parser(t_lexer *lexer);
void		parser_expect(t_parser *parser, int type);
t_ast		*parser_parse_commands(t_parser *parser);
t_ast		*parser_parse_command(t_parser *parser);
t_ast		*parse_echo(t_parser *parser);
t_ast		*parse_cd(t_parser *parser);
t_ast		*parse_pwd(t_parser *parser);
t_ast		*parse_export(t_parser *parser);
// t_ast		*(t_parser *parser);


#endif /* ifndef PARSER_H */
