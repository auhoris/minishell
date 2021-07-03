#include "executor.h"

// i love you norminette
static int	end_pipe(t_exec *exec, t_ast *exec_node, t_env_list *env, int fd[])
{
	int	out;

	exec->piperead = fd[0];
	close(exec->pipewrite);
	exec->pipewrite = STDOUT_FILENO;
	out = executor_simplecommand(exec, exec_node, env);
	close(exec->piperead);
	return (out);
}

static int	start_pipe(t_exec *exec, t_ast *node, t_env_list *env, int fd[])
{
	int	out;

	exec->pipewrite = fd[1];
	out = executor_simplecommand(exec, node->table_value[0], env);
	exec->piperead = fd[0];
	return (out);
}

/* exec->pipewrite = fd[1];
out = executor_simplecommand(exec, node->table_value[0], env);
exec->piperead = fd[0]; */
int	executor_pipe(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	int		fd[2];
	t_ast	*exec_node;

	if (pipe(fd) == -1)
		return (ERROR);
	out = start_pipe(exec, node, env, fd);
	exec_node = node->table_value[1];
	/* printf("%p\n", exec_node);
	printf("%p\n", exec_node->cmd_name); */
	while (exec_node->e_nodetype == NODE_PIPE)
	{
		close(exec->pipewrite);
		if (pipe(fd) == -1)
		{
			close(exec->piperead);
			return (ERROR);
		}
		exec->pipewrite = fd[1];
		if (exec_node->table_value[0])
			out = executor_simplecommand(exec, exec_node->table_value[0], env);
		close(exec->piperead);
		exec->piperead = fd[0];
		exec_node = exec_node->table_value[1];
	}
	out = end_pipe(exec, exec_node, env, fd);
	return (out);
}
/* exec->piperead = fd[0];
close(exec->pipewrite);
exec->pipewrite = STDOUT_FILENO;
out = executor_simplecommand(exec, exec_node, env);
close(exec->piperead); */
