#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

static void	execution_echo(t_ast *node)
{
	size_t	i;

	i = 0;
	write (1, "\n", 1);
	while (i < node->argc)
	{
		if (i != 0)
			write (1, " ", 1);
		write(1, node->argv[i], ft_strlen(node->argv[i]));
		i++;
	}
}

static int	execution_cd(t_ast *node, t_env_list *env)
{
	int	out;
	char	pwd_dir[256];

	if (getcwd(pwd_dir, 256) == NULL)
		return (ERROR_MALLOC);
	if (set_old_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	out = chdir(node->argv[0]);
	ft_bzero(pwd_dir, 256);
	if (getcwd(pwd_dir, 256) == NULL)
		return (ERROR_MALLOC);
	if (out != 0)
	{
		write(1, "\nminishell: cd: ", 16);
		write(1, node->argv[0], ft_strlen(node->argv[0]));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		// printf("\nminishell: cd: %s: %s", node->argv[0], strerror(errno));
	}
	else
	{
		if (set_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

static int execution_pwd(t_env_list *env)
{
	int	out;
	char	*pwd_dir;

	pwd_dir = NULL;
	out = get_pwd_dir(env, &pwd_dir);
	if (out == OUT)
	{
		write(1, "\n", 1);
		write(1, pwd_dir, ft_strlen(pwd_dir));
	}
	return (out);
}

static int	execution_export(t_ast *node, t_env_list *env)
{
	size_t	i;
	int		out;

	i = 0;
	while (i < node->argc)
	{
		out = set_key_value(node->argv[i], env);
		if (out == ERROR_MALLOC)
			return (ERROR_MALLOC);
		i++;
	}
	return (OUT);
}

int	check_builtin(t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(node);
	if (ft_strcmp(node->cmd_name, "cd") == 0)
		out = execution_cd(node, env);
	if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(env);
	if (ft_strcmp(node->cmd_name, "export") == 0)
		out = execution_export(node, env);
	return (out);
}