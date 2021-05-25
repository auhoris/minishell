#include "../includes/types.h"
#include "../includes/minishell.h"
#include "../includes/env.h"
#include "executor.h"

static void	executor_root(t_ast *node, t_env_list *env)
{
	size_t	i;

	i = 0;
	while (i < node->table_size)
	{
		detour_tree(node->table_value[i], env);
		i++;
	}
}

static int	executor_simplecommand(t_ast *node, t_env_list *env)
{
	// int	out;

	if (check_builtin(node, env) == OUT)
		return (OUT);
	return (OUT);
}

int	detour_tree(t_ast *node, t_env_list *env)
{
	// int	out;
	if (node->e_nodetype == NODE_ROOT)
		executor_root(node, env);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		executor_simplecommand(node, env);
	return (OUT);
}