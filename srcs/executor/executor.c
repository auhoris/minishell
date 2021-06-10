#include "../includes/types.h"
#include "../includes/minishell.h"
#include "../includes/env.h"
#include "executor.h"
#include <stdio.h>
#include <unistd.h>

t_exec	*init_exec(t_ast *root, size_t pipes)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (exec == NULL)
		return (NULL);
	exec->root = root;
	exec->node = root;
	exec->curr_node_type = root->e_nodetype;
	exec->pipes = pipes;
	exec->tempin = -1;
	exec->tempout = -1;
	exec->exit_status = OK;
	exec->fd[0] = -1;
	exec->fd[1] = -1;
	exec->r_or_w = -1;
	exec->pids = NULL;
	exec->size_pids = 0;
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
	if (exec->fd[0] != -1)
	{
		if (exec->r_or_w == 1)
			dup2(exec->fd[1], STDOUT_FILENO);
		else if (exec->r_or_w == 0)
			dup2(exec->fd[0], STDIN_FILENO);
	}
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
	if (exec->fd[0] != -1)
	{
		dup2(exec->tempin, STDIN_FILENO);
		close(exec->tempin);
		dup2(exec->tempout, STDOUT_FILENO);
		close(exec->tempout);
	}
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

static int	executor_pipe(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	if (pipe(exec->fd) == -1)
	{
		perror("");
		return (ERROR_PIPE);
	}
	exec->r_or_w = 1;
	out = detour_tree(exec, node->table_value[0], env);
	exec->r_or_w = 0;
	out = detour_tree(exec, node->table_value[1], env);
	close(exec->fd[1]);
	close(exec->fd[0]);
	exec->r_or_w = -1;
	return (out);
}

static int	executor_simplecommand(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	exec->tempout = dup(STDOUT_FILENO);
	exec->tempin = dup(STDIN_FILENO);
	check_redirection(exec, node);
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
