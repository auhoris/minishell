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

static void	bad_command(char *command, int no_path_f)
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
	if (bool || no_path_f)
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

static int	execute_other_command(t_exec *exec, char **args,
				char **envp, int no_path_f)
{
	int			pid;

	pid = fork();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		isredir(exec);
		close(exec->tempin);
		close(exec->tempout);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		tcsetattr(0, TCSANOW, data_processing->term_default);
		if (execve(args[0], args, envp) == -1)
		{
			bad_command(args[0], no_path_f);
			exit(ERROR_BAD_COMMAND);
		}
	}
	if (append_pid(exec, pid) != OK)
		return (ERROR_MALLOC);
	return (OK);
}

int	other_command(t_exec *exec, t_ast *node, t_env_list *env)
{
	char	**env_array;
	char	**path_array;
	char	**args;
	int		error;
	int		ret_handler;

	exec->n_flag = FALSE;
	ret_handler = get_path_array(env, &path_array);
	if (ret_handler == ERROR_MALLOC)
		return (ERROR_MALLOC);
	else if (ret_handler == NO_PATH)
		args = create_args(node, &error, NULL);
	else
		args = create_args(node, &error, path_array);
	if (args == NULL && error == ERROR_MALLOC)
		return (ERROR_MALLOC);
	env_array = create_env(env);
	if (env_array == NULL)
	{
		clear_array(args, ALL_ARRAY);
		return (ERROR_MALLOC);
	}
	execute_other_command(exec, args, env_array, ret_handler);
	free_arr(args, env_array);
	return (OUT);
}

int	check_builtin(t_exec *exec, t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (node->cmd_name == NULL)
		return (out);
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(exec, node);
	else if (ft_strcmp(node->cmd_name, "cd") == 0)
		out = execution_cd(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(exec, node);
	else if (ft_strcmp(node->cmd_name, "export") == 0)
		out = execution_export(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "env") == 0)
		out = execution_env(exec, node, env);
	else if (ft_strcmp(node->cmd_name, "unset") == 0)
		out = execution_unset(exec, node, &env);
	else if (ft_strcmp(node->cmd_name, "exit") == 0)
		out = executor_exit(node->argc, node->argv, &env);
	else
		out = other_command(exec, node, env);
	return (out);
}
