#include "../includes/types.h"
#include "../includes/minishell.h"
#include "../includes/env.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_size_t.h>
#include <unistd.h>

t_exec	*init_exec(t_ast *root)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	exec->root = root;
	exec->node = root;
	exec->curr_node_type = root->e_nodetype;
	exec->tempin = -1;
	exec->tempout = -1;
	exec->exit_status = OK;
	exec->is_redir = 0;
	exec->pids = NULL;
	exec->size_pids = 0;
	exec->piperead = STDIN_FILENO;
	exec->pipewrite = STDOUT_FILENO;
	return (exec);
}

static int	wait_pids(t_exec *exec, int cnt)
{
	size_t	i;
	int		waiting;
	int		temp;

	i = 0;
	if (exec->size_pids == 0)
		return (OK);
	if (cnt == 0)
		ft_putchar('\n');
	while (i < exec->size_pids)
	{
		temp = waitpid(exec->pids[i], &waiting, 0);
		if ((temp = WIFEXITED(waiting)))
		{
			exec->exit_status = WEXITSTATUS(waiting);
		}
		i++;
	}
	return (OK);
}

static int	executor_root(t_exec *exec, t_ast *node, t_env_list *env)
{
	// size_t	i;
	int		out;

	exec->i = 0;
	out = OUT;
	while (exec->i < node->table_size)
	{
		out = detour_tree(exec, node->table_value[exec->i], env);
		if (out == ERROR_EXIT)
			return (out);
		wait_pids(exec, exec->i);
		exec->i++;
	}
	return (out);
}

int	executor_simplecommand(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	/* if (ft_strcmp(node->cmd_name, "") == 0)
		return (OUT); */
	set_redirection(exec, node);
	out = check_builtin(exec, node, env);
	restore_std(exec, node);
	return (out);
}

int	detour_tree(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (node->e_nodetype == NODE_ROOT)
		return (executor_root(exec, node, env));
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		return (executor_simplecommand(exec, node, env));
	if (node->e_nodetype == NODE_PIPE)
		return (executor_pipe(exec, node, env));
	return (out);
}
