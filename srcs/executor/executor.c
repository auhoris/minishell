#include "../includes/types.h"
#include "../includes/minishell.h"
#include "../includes/env.h"
#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_size_t.h>
#include <unistd.h>

t_exec	*init_exec(t_ast *root, size_t pipes)
{
	t_exec	*exec;
	(void)pipes;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	exec->root = root;
	exec->node = root;
	exec->curr_node_type = root->e_nodetype;
	exec->tempin = -1;
	exec->tempout = -1;
	exec->exit_status = OK;
	exec->r_or_w = -1;
	exec->pids = NULL;
	exec->size_pids = 0;
	exec->piperead = STDIN_FILENO;
	exec->pipewrite = STDOUT_FILENO;
	return (exec);
}

static int	executor_root(t_exec *exec, t_ast *node, t_env_list *env)
{
	size_t	i;
	int	out;

	i = 0;
	out = OUT;
	while (i < node->table_size)
	{
		out = detour_tree(exec, node->table_value[i], env);
		if (out != OUT)
			return (out);
		i++;
	}
	return (out);
}

int	check_redirection(t_exec *exec, t_ast *node)
{
	exec->tempin = dup(STDIN_FILENO);
	exec->tempout = dup(STDOUT_FILENO);
	if (exec->piperead != STDIN_FILENO)
		dup2(exec->piperead, STDIN_FILENO);
	if (exec->pipewrite != STDOUT_FILENO)
		dup2(exec->pipewrite, STDOUT_FILENO);
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(node->fd_in, STDIN_FILENO);
		close(node->fd_in);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(node->fd_out, STDOUT_FILENO);
		close(node->fd_out);
	}
	return (OK);
}

int	restore_std(t_exec *exec, t_ast *node)
{
	if (exec->piperead != STDIN_FILENO)
		dup2(exec->tempin, STDIN_FILENO);
	if (exec->pipewrite != STDOUT_FILENO)
		dup2(exec->tempout, STDOUT_FILENO);
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(exec->tempin, STDIN_FILENO);
		close(exec->tempin);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(exec->tempout, STDOUT_FILENO);
		close(exec->tempout);
	}
	return (OK);
}
static int	executor_simplecommand(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	check_redirection(exec, node);
	out = check_builtin(exec, node, env);
	restore_std(exec, node);
	close(exec->tempout);
	close(exec->tempin);
	return (out);
}

static int	executor_pipe(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	int		fd[2];
	t_ast	*exec_node;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (ERROR);
	}
	exec->pipewrite = fd[1];
	out = executor_simplecommand(exec, node->table_value[0], env);
	exec->piperead = fd[0];
	exec_node = node->table_value[1];
	while (exec_node->e_nodetype == NODE_PIPE)
	{
		close(exec->pipewrite);
		pipe(fd);
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

