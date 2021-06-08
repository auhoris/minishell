#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

static int	execute_other_command(char **args, char **envp)
{
	int	pid;
	int	exit_status;
	int	wating;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: ");
		return (ERROR);
	}
	if (pid == 0)
		execve(args[0], args, envp);
	wait(&wating);
	if (WIFEXITED(wating))
	{
		exit_status = WEXITSTATUS(wating);
		if (exit_status == OK)
			return (OK);
		return (ERROR);
	}
	return (OK);
}

int	other_command(t_ast *node, t_env_list *env)
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
	write(1, "\n", 1);
	if (execute_other_command(args, env_array) == ERROR)
	{
		clear_array(args, ALL_ARRAY);
		clear_array(env_array, ALL_ARRAY);
	}
	return (OUT);
}

int	check_builtin(t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(node);
	else if (ft_strcmp(node->cmd_name, "cd") == 0)
		out = execution_cd(node, env);
	else if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(env);
	else if (ft_strcmp(node->cmd_name, "export") == 0)
		out = execution_export(node, env);
	else if (ft_strcmp(node->cmd_name, "env") == 0)
		out = execution_env(node, env);
	else if (ft_strcmp(node->cmd_name, "exit") == 0)
		out = ERROR_EXIT;
	else
		out = other_command(node, env);
	return (out);
}
