#include "includes/visitor.h"
#include <sys/_types/_size_t.h>
#include <unistd.h>

void	visitor_visit_vardef(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("name = %s\n", node->var_name);
	printf("value = %s\n", node->var_value);
}

void	visitor_visit_nodes(t_ast *node)
{
	printf("\n%zu\n", node->argc);
	if (node->e_nodetype == NODE_ROOT)
		visitor_visit_root(node);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		visitor_visit_simplecommand(node);
	if (node->e_nodetype == NODE_PIPE)
		visitor_visit_pipe(node);
	if (node->e_nodetype == NODE_VARDEF)
		visitor_visit_vardef(node);
}

void	visitor_visit_root(t_ast *node)
{
	size_t	i;

	i = 0;
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("node->err_handler='%d'\n", node->err_handler);
	while (i < node->table_size)
	{
		visitor_visit_nodes(node->table_value[i]);
		i++;
	}
}

void	visitor_visit_pipe(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("node->err_handler='%d'\n", node->err_handler);
	visitor_visit_nodes(node->table_value[0]);
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("node->err_handler='%d'\n", node->err_handler);
	visitor_visit_nodes(node->table_value[1]);
}

void	visitor_visit_simplecommand(t_ast *node)
{
	size_t	i;

	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("node->err_handler='%d'\n", node->err_handler);
	printf("----command name = %s----\n", node->cmd_name);
	i = 0;
	while (i < node->argc)
	{
		printf("%zu: argv[%zu] = %s\n", i, i, node->argv[i]);
		i++;
	}
	if (node->out_file)
		printf("fd_out='%d'\tout_file='%s'\n", node->fd_out, node->out_file);
	if (node->in_file)
		printf("fd_in='%d'\tin_file='%s'\n", node->fd_in, node->in_file);
	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	printf("\n<========>\n");
}

char	*print_node_type(int type)
{
	switch (type) {
		case NODE_ROOT: return ("NODE_ROOT");
		case NODE_PIPE: return ("NODE_PIPE");
		case NODE_SIMPLECOMMAND: return ("NODE_SIMPLECOMMAND");
		case NODE_VARDEF: return ("NODE_VARDEF");
		default: return ("Undefined node type");
	}
}
