#include "../includes/types.h"
#include "../includes/minishell.h"
#include "../includes/env.h"
#include "executor.h"

static int	executor_root(t_ast *node, t_env_list *env)
{
	size_t	i;
	int	out;

	i = 0;
	out = OUT;
	while (i < node->table_size)
	{
		out = detour_tree(node->table_value[i], env);
		if (out != OUT)
			return (out);
		i++;
	}
	return (out);
}

static int	executor_simplecommand(t_ast *node, t_env_list *env)
{
	int	out;

	out = check_builtin(node, env);
	return (out);
}

int	detour_tree(t_ast *node, t_env_list *env)
{
	int	out;
	out = OUT;
	if (node->e_nodetype == NODE_ROOT)
		out = executor_root(node, env);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		out = executor_simplecommand(node, env);
	return (out);
}