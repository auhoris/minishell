#include "includes/visitor.h"
#include <sys/_types/_size_t.h>

void	visitor_visit_vardef(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("name = %s\n", node->var_name);
	printf("value = %s\n", node->var_value);
}

void	visitor_visit_nodes(t_ast *node)
{
	if (node->e_nodetype == NODE_ROOT)
		visitor_visit_root(node);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		visitor_visit_simplecommand(node);
	if (node->e_nodetype == NODE_PIPE)
		visitor_visit_pipe(node);
	if (node->e_nodetype == NODE_VARDEF)
		visitor_visit_vardef(node);
	if (node->e_nodetype == NODE_LREDIRECT
	|| node->e_nodetype == NODE_RREDIRECT
	|| node->e_nodetype == NODE_DOUBLE_REDIRECT)
		visitor_visit_redirect(node);
}

void	visitor_visit_root(t_ast *node)
{
	size_t	i;

	i = 0;
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	while (i < node->table_size)
	{
		visitor_visit_nodes(node->table_value[i]);
		i++;
	}
}
void	visitor_visit_redirect(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	visitor_visit_nodes(node->table_value[0]);
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	visitor_visit_nodes(node->table_value[1]);
}

void	visitor_visit_pipe(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	visitor_visit_nodes(node->table_value[0]);
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	visitor_visit_nodes(node->table_value[1]);
}

void	visitor_visit_simplecommand(t_ast *node)
{
	size_t	i;

	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("command name = %s\t", node->cmd_name);
	i = 0;
	while (i < node->argc)
	{
		printf("argv[%zu] = %s\t", i, node->argv[i]);
		i++;
	}
	printf("\n\n<========>\n\n");

}

 char	*print_node_type(int type)
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
}
