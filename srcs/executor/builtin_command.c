#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <string.h>

void	execution_echo(t_ast *node)
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

int	execution_cd(t_ast *node, t_env_list *env)
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

int execution_pwd(t_env_list *env)
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

int	execution_export(t_ast *node, t_env_list *env)
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

int	execution_env(t_ast *node, t_env_list *env)
{
	if (node->argc > 1)
		write(1, "\nenv must be without any options or arguments", 45);
	else
	{
		while (env->next != NULL)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->key, ft_strlen(env->value));
			write(1, "\n", 1);
			env = env->next;
		}
		write(1, env->key, ft_strlen(env->key));
		write(1, "=", 1);
		write(1, env->value, ft_strlen(env->value));
	}
	return (OUT);
}