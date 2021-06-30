#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "../includes/minishell.h"
#include "executor.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

static void	bad_command(char *command)
{
	size_t	i;
	int		bool;

	i = 0;
	bool = FALSE;
	while (command[i])
	{
		if (command[i] == '/')
		{
			bool = TRUE;
			break ;
		}
		i++;
	}
	if (bool)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

/* if (data_processing->cmd_i == 0)
	ft_putchar_fd('\n', exec->tempout); */
/* ft_putstr_fd("minishell: ", exec->tempout);
ft_putstr_fd(command, exec->tempout);
if (exec->root->table_size > 1 && exec->i + 1 != exec->node->table_size)
	ft_putstr_fd(": command not found", exec->tempout);
else
	ft_putstr_fd(": command not found\n", exec->tempout); */

static int	execute_other_command(t_exec *exec, char **args, char **envp)
{
	int			pid;

	pid = fork();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		if (!exec->is_redir)
		{
			dup2(exec->piperead, STDIN_FILENO);
			dup2(exec->pipewrite, STDOUT_FILENO);
			if (exec->piperead != STDIN_FILENO)
				close(exec->piperead);
			if (exec->pipewrite != STDOUT_FILENO)
				close(exec->pipewrite);
		}
		close(exec->tempin);
		close(exec->tempout);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		tcsetattr(0, TCSANOW, data_processing->term_default);
		if (execve(args[0], args, envp) == -1)
		{
			bad_command(args[0]);
			exit(ERROR_BAD_COMMAND);
		}
	}
	if (append_pid(exec, pid) != OK)
		return (ERROR_MALLOC);
	return (OK);
}

// Чистить args и env_array надо всегда, вроде бы
int	other_command(t_exec *exec, t_ast *node, t_env_list *env)
{
	char	**env_array;
	char	**path_array;
	char	**args;
	int		error;

	// data_processing->n_flag = FALSE;
	if (get_path_array(env, &path_array) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	args = create_args(exec, node, &error, path_array);
	// if (args == NULL && error == ERROR_BAD_COMMAND)
	// 	return (ERROR_BAD_COMMAND);
	// else
	if (args == NULL && error == ERROR_MALLOC)
		return (ERROR_MALLOC);
	env_array = create_env(env);
	if (env_array == NULL)
	{
		clear_array(args, ALL_ARRAY);
		return (ERROR_MALLOC);
	}
	execute_other_command(exec, args, env_array);
	free_arr(args);
	free_arr(env_array);
	return (OUT);
}

int	check_builtin(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	data_processing->n_flag = TRUE;
	if (node->cmd_name == NULL)
		return (out);
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(exec, node);
	else if (ft_strcmp(node->cmd_name, "cd") == 0)
		out = execution_cd(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "export") == 0)
		out = execution_export(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "env") == 0)
		out = execution_env(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "unset") == 0)
		out = execution_unset(node, &env);
	else if (ft_strcmp(node->cmd_name, "exit") == 0)
		out = executor_exit(node->argc, node->argv, &env);
	else
		out = other_command(exec, node, env);
	return (out);
}
