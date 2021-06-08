#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

static int	execute_other_command(t_exec *exec, char **args, char **envp)
{
	int	pid;
	// int	exit_status;
	int	wating;

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
			/* printf("exec->fd[0] = %d\n", exec->fd[0]);
			printf("exec->fd[1] = %d\n", exec->fd[1]); */
			dup2(exec->fd[1], STDOUT_FILENO);
			close(exec->fd[1]);
			close(exec->fd[0]);
		}
		else if (exec->r_or_w == 0)
		{
			/* printf("exec->fd[0] = %d\n", exec->fd[0]);
			printf("exec->fd[1] = %d\n", exec->fd[1]); */
			dup2(exec->fd[0], STDIN_FILENO);
			close(exec->fd[1]);
			close(exec->fd[0]);
		}
		/* printf("exec->fd[0] = %d\n", exec->fd[0]);
		printf("exec->fd[1] = %d\n", exec->fd[1]); */
		/* printf("%d\n", STDOUT_FILENO);
		printf("%d\n", STDIN_FILENO); */
		execve(args[0], args, envp);
	}
	printf("%d\n", STDOUT_FILENO);
	printf("%d\n", STDIN_FILENO);
	printf("%s", args[0]);
	wait(&wating);
	/* if (WIFEXITED(wating))
	{
		exit_status = WEXITSTATUS(wating);
		if (exit_status == OK)
		{
			return (OK);
		}
		return (ERROR);
	} */
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
	write(1, "\n", 1);
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
		out = other_command(exec, node, env);
	// printf("check_builtin\n");
	return (out);
}
