#include "executor.h"

/* static int	handle_piping(t_exec *exec, t_ast *exec_node, t_env_list *env)
{
	int	out;
	int	fd[2];

	close(exec->pipewrite);
	if (pipe(fd) == -1)
	{
		close(exec->piperead);
		return (ERROR);
	}
	exec->pipewrite = fd[1];
	out = executor_simplecommand(exec, exec_node->table_value[0], env);
	close(exec->piperead);
	exec->piperead = fd[0];
	exec_node = exec_node->table_value[1];
	return (out);
} */

int	executor_pipe(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	int		fd[2];
	t_ast	*exec_node;

	if (pipe(fd) == -1)
		return (ERROR);
	exec->pipewrite = fd[1];
	out = executor_simplecommand(exec, node->table_value[0], env);
	exec->piperead = fd[0];
	exec_node = node->table_value[1];
	while (exec_node->e_nodetype == NODE_PIPE)
	{
		close(exec->pipewrite);
		if (pipe(fd) == -1)
		{
			close(exec->piperead);
			return (ERROR);
		}
		exec->pipewrite = fd[1];
		out = executor_simplecommand(exec, exec_node->table_value[0], env);
		close(exec->piperead);
		exec->piperead = fd[0];
		exec_node = exec_node->table_value[1];
	}
	exec->piperead = fd[0];
	close(exec->pipewrite);
	exec->pipewrite = STDOUT_FILENO;
	out = executor_simplecommand(exec, exec_node, env);
	close(exec->piperead);
	return (out);
}
