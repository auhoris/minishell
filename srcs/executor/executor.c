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
	return (exec);
}

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

/* int	check_redirection()
{
	return (OK);
}

int	restore_std()
{
	return (OK);
} */

static int	executor_pipe(t_ast *node, t_env_list *env)
{
	int	out;
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("");
		return (ERROR_PIPE);
	}
	out = detour_tree(node->table_value[0], env);
	out = detour_tree(node->table_value[0], env);
	return (out);
}

static int	executor_simplecommand(t_ast *node, t_env_list *env)
{
	int	out;
	int	tempin;
	int	tempout;

	tempout = dup(STDOUT_FILENO);
	tempin = dup(STDIN_FILENO);
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
	out = check_builtin(node, env);
	if (node->fd_in != STDIN_FILENO)
	{
		dup2(tempin, STDIN_FILENO);
		close(tempin);
	}
	if (node->fd_out != STDOUT_FILENO)
	{
		dup2(tempout, STDOUT_FILENO);
		close(tempout);
	}
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
	if (node->e_nodetype == NODE_PIPE)
		executor_pipe(node, env);
	return (out);
}
