#include "includes/ast.h"
#include <sys/_types/_size_t.h>

t_ast	*init_node(int type)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->e_nodetype = type;
	ast->cmd_name = NULL;
	ast->argc = 0;
	ast->argv = NULL;
	ast->flags = NULL;
	ast->fd_pipe_read = -1;
	ast->fd_pipe_write = -1;
	ast->redirect_in = NULL;
	ast->redirect_out = NULL;
	ast->table_value = NULL;
	ast->table_size = 0;
	return (ast);
}
