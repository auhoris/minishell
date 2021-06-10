#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

static int	append_pid(t_exec *exec, int pid)
{
	if (exec->size_pids == 0)
	{
		exec->pids = ft_calloc(1, sizeof(int));
		if (exec->pids == NULL)
			return (ERROR_MALLOC);
		exec->pids[exec->size_pids++] = pid;
	}
	else
	{
		exec->size_pids++;
		exec->pids = ft_realloc(exec->pids, exec->size_pids * sizeof(int),
				(exec->size_pids - 1) * sizeof(int));
		if (exec->pids == NULL)
			return (ERROR_MALLOC);
		exec->pids[exec->size_pids - 1] = pid;
	}
	return (OK);
}

static int	execute_other_command(t_exec *exec, char **args, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (ERROR);
	}
	if (pid == 0)
	{
		if (exec->r_or_w == 1)
		{
			dup2(exec->fd[1], STDOUT_FILENO);
			close(exec->fd[1]);
			close(exec->fd[0]);
		}
		else if (exec->r_or_w == 0)
		{
			dup2(exec->fd[0], STDIN_FILENO);
			close(exec->fd[1]);
			close(exec->fd[0]);
		}
		close(exec->tempout);
		close(exec->tempin);
		execve(args[0], args, envp);
	}
	if (append_pid(exec, pid) != OK)
			return (ERROR);
	return (OK);
}

int	other_command(t_exec *exec, t_ast *node, t_env_list *env)
{
	char	**env_array;
	char	**args;

	args = create_args(node);
	if (args == NULL)
		return (ERROR_MALLOC);
	env_array = create_env(env);
	if (env_array == NULL)
	{
		clear_array(args, ALL_ARRAY);
		return(ERROR_MALLOC);
	}
	if (execute_other_command(exec, args, env_array) == ERROR)
	{
		clear_array(args, ALL_ARRAY);
		clear_array(env_array, ALL_ARRAY);
	}
	return (OUT);
}

int	check_builtin(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(exec, node);
	else if (ft_strcmp(node->cmd_name, "cd") == 0)
		out = execution_cd(node, env);
	else if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(env);
	else if (ft_strcmp(node->cmd_name, "export") == 0)
		out = execution_export(node, env);
	else if (ft_strcmp(node->cmd_name, "env") == 0)
		out = execution_env(node, env);
	else if (ft_strcmp(node->cmd_name, "unset") == 0)
		out = execution_unset(node, &env);
	else if (ft_strcmp(node->cmd_name, "exit") == 0)
		out = ERROR_EXIT;
	else
		out = other_command(exec, node, env);
	return (out);
}
