#include "includes/ast.h"
#include <sys/_types/_size_t.h>
#include <unistd.h>
#include "includes/errors.h"

t_ast	*init_node(int type)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->e_nodetype = type;
	ast->table_value = NULL;
	ast->table_size = 0;
	ast->cmd_name = NULL;
	ast->argv = NULL;
	ast->argc = 0;
	ast->fd_out = STDOUT_FILENO;
	ast->fd_in = STDIN_FILENO;
	ast->err_handler = OK;
	return (ast);
}

t_ast	*ast_error_handler(t_ast *node)
{
	node->err_handler = ERROR;
	return (node);
}
