#include "includes/ast.h"
#include "includes/parser.h"

void	free_lexer(t_lexer *lexer)
{
	free(lexer->content);
	free(lexer);
}

void	free_parser(void *parser)
{
	free_lexer(((t_parser *)parser)->lexer);
	destroy_token(((t_parser *)parser)->cur_tok);
	free(parser);
}

void	free_root_parser(void *root)
{
	free_nodes(((t_ast *)root));
}

void	free_exec(void *exec)
{
	free_nodes(((t_exec *)exec)->root);
	free(((t_exec *)exec)->pids);
	free(exec);
}

int	free_unique(int code, void *content, void(*del)(void *))
{
	(*del)(content);
	return (code);
}
