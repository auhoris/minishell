#include "includes/visitor.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

void	free_nodes(t_ast *node);
/* void	free_simplecommand(t_ast *node);
void	free_pipe(t_ast *node);
void	free_root(t_ast *node);
void	free_redirect(t_ast *node); */

void	free_vardef(t_ast *node)
{
	(void)node;
}

void	safe_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

static void	free_root(t_ast *node)
{
	size_t	i;

	i = 0;
	while (i < node->table_size)
	{
		free_nodes(node->table_value[i]);
		safe_free(node->table_value[i]);
		i++;
	}
	safe_free(node->table_value);
	// printf("%p\n", node);
}

static void	free_redirect(t_ast *node)
{
	free_nodes(node->table_value[0]);
	safe_free(node->table_value[0]);
	free_nodes(node->table_value[1]);
	safe_free(node->table_value[1]);
}

static void	free_pipe(t_ast *node)
{
	free_nodes(node->table_value[0]);
	safe_free(node->table_value[0]);
	free_nodes(node->table_value[1]);
	safe_free(node->table_value[1]);
}

static void	free_simplecommand(t_ast *node)
{
	size_t	i;

	i = 0;
	if (node == NULL)
		return ;
	safe_free(node->cmd_name);
	while (i < node->argc)
	{
		safe_free(node->argv[i]);
		i++;
	}
	safe_free(node->argv);
	/* printf("%p\n", node);
	printf("%d\n", node->e_nodetype); */
}

void	free_nodes(t_ast *node)
{
	if (node->e_nodetype == NODE_ROOT)
		free_root(node);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		free_simplecommand(node);
	if (node->e_nodetype == NODE_PIPE)
		free_pipe(node);
	if (node->e_nodetype == NODE_VARDEF)
		free_vardef(node);
	if (node->e_nodetype == NODE_LREDIRECT
		|| node->e_nodetype == NODE_RREDIRECT
		|| node->e_nodetype == NODE_DOUBLE_REDIRECT)
		free_redirect(node);
}
