#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

// static int	call_execve(char **args, char **env_array)
// {

// }

static int	outher_command(t_ast *node, t_env_list *env)
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
	execve(args[0], args, env_array);
	// perror("Error: ");
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
		out = outher_command(node, env);
	return (out);
}