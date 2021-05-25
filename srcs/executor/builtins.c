#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
// #include <dirent.h>

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
	char	*pwd_dir;

	out = chdir(node->argv[0]);
	pwd_dir = NULL;
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
		out = get_pwd_dir(env, &pwd_dir);
		if (out != OUT)
			return (OUT);
		if (ft_strncmp(node->argv[0], pwd_dir, ft_strlen(pwd_dir)))
		{

		}
	}
	return (OUT);
}

static int execution_pwd(t_ast *node, t_env_list *env)
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
	else
	{
		node = NULL; // временно
//		error :)
	}
	return (out);
}

int	check_builtin(t_ast *node, t_env_list *env)
{
	int	out;

	out = OUT;
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		execution_echo(node);
	if (ft_strcmp(node->cmd_name, "cd") == 0)
		execution_cd(node, env);
	if (ft_strcmp(node->cmd_name, "pwd") == 0)
		out = execution_pwd(node, env);

	return (out);
}