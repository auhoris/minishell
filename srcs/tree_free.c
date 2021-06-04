#include "includes/visitor.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

void	free_root(t_ast *node)
{
	size_t	i;

	i = 0;
	while (i < node->table_size)
	{
		free_nodes(node->table_value[i]);
		i++;
	}
}

void	free_redirect(t_ast *node)
{
	free_nodes(node->table_value[0]);
	free_nodes(node->table_value[1]);
}

void	free_pipe(t_ast *node)
{
	free_nodes(node->table_value[0]);
	free_nodes(node->table_value[1]);
}

void	free_simplecommand(t_ast *node)
{
	size_t	i;

	i = 0;
	while (i < node->argc)
	{
		free(node->argv[i]);
		i++;
	}
}

/* char	*print_node_type(int type)
{
	switch (type) {
		case NODE_ROOT: return ("NODE_ROOT");
		case NODE_PIPE: return ("NODE_PIPE");
		case NODE_LREDIRECT: return ("NODE_LREDIRECT");
		case NODE_RREDIRECT: return ("NODE_RREDIRECT");
		case NODE_DOUBLE_REDIRECT: return ("NODE_DOUBLE_REDIRECT");
		case NODE_SIMPLECOMMAND: return ("NODE_SIMPLECOMMAND");
		case NODE_VARDEF: return ("NODE_VARDEF");
		default: return ("Undefined node type");
	}
} */

void	free_nodes(t_ast *node)
{
	if (node->e_nodetype == NODE_ROOT)
		free_root(node);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		free_simplecommand(node);
	if (node->e_nodetype == NODE_PIPE)
		free_pipe(node);
	/* if (node->e_nodetype == NODE_LREDIRECT
		|| node->e_nodetype == NODE_RREDIRECT
		|| node->e_nodetype == NODE_DOUBLE_REDIRECT)
		free_redirect(node); */
}
