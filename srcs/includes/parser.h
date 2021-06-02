#ifndef PARSER_H
# define PARSER_H

# include "env.h"
# include "minishell.h"
# include "lexer.h"
# include "token.h"
# include "ast.h"

typedef struct s_parser
{
	t_lexer		*lexer;
	t_token		*prev_token;
	t_token		*cur_tok;
	t_env_list	*env;
}			t_parser;

t_parser	*init_parser(t_lexer *lexer, t_env_list *env);
int			parser_next_token(t_parser *parser);
t_ast		*parser_parse_commands(t_parser *parser);
t_ast		*parser_parse_pipe(t_ast *left_node, t_parser *parser);
t_ast		*parser_parse_command(t_parser *parser);
int			parser_parse_redirect(t_parser *parser, t_ast *node);
t_ast		*parser_parse_simple_command(t_parser *parser);
char		*parser_get_cmd_name(t_parser *parser);
char		*parser_get_dollar_value(t_token *token);

#endif /* ifndef PARSER_H */
