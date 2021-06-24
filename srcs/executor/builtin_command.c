#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void	handle_echo_output(t_exec *exec, t_ast *node, size_t pos, size_t n_flag)
{
	if (pos != (size_t)n_flag)
		ft_putchar(' ');
	if (ft_strcmp(node->argv[pos], "$?") == 0)
		ft_putstr(ft_itoa(exec->exit_status));
	else
		ft_putstr(node->argv[pos]);
}

void	execution_echo(t_exec *exec, t_ast *node)
{
	size_t	i;
	int		n_flag;

	n_flag = 0;
	i = 0;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	if (node->argv == NULL)
	{
		if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
			ft_putchar('\n');
		return ;
	}
	else if (ft_strcmp(node->argv[i], "-n") == 0)
		n_flag = ++i;
	while (i < node->argc)
	{
		handle_echo_output(exec, node, i, n_flag);
		i++;
	}
	if (!n_flag && (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO))
		ft_putchar('\n');
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		exec->flag_echo = n_flag;
}

int	execution_cd(t_ast *node, t_env_list *env)
{
	int		out;
	char	pwd_dir[256];

	if (getcwd(pwd_dir, 256) == NULL)
		return (ERROR_MALLOC);
	if (set_old_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	if (node->argv == NULL)
		out = chdir(get_value_by_key("HOME", &env));
	else
		out = chdir(node->argv[0]);
	ft_bzero(pwd_dir, 256);
	if (getcwd(pwd_dir, 256) == NULL)
		return (ERROR_MALLOC);
	if (out != 0 && node->argv != NULL)
	{
		write(1, "\nminishell: cd: ", 16);
		write(1, node->argv[0], ft_strlen(node->argv[0]));
		write(1, ": ", 2);
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	}
	else
		if (set_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	return (OUT);
}

int	execution_pwd(t_env_list *env)
{
	int		out;
	char	*pwd_dir;

	pwd_dir = NULL;
	out = get_pwd_dir(env, &pwd_dir);
	if (out == OUT)
	{
		ft_putstr("\n");
		ft_putstr(pwd_dir);
	}
	return (out);
}

int	execution_export(t_ast *node, t_env_list *env)
{
	size_t	i;
	int		out;

	i = 0;
	if (node->argc == 0)
	{
		write_export(env);
		return (OUT);
	}
	while (i < node->argc)
	{
		out = set_key_value(node->argv[i], env);
		if (out == ERROR_MALLOC)
			return (ERROR_MALLOC);
		i++;
	}
	write(1, "\n", 1);
	return (OUT);
}

int	execution_unset(t_ast *node, t_env_list **env)
{
	size_t		i;

	if (!(*env))
		return (OUT);
	i = 0;
	while (i < node->argc)
	{
		unset_env_elem(env, node->argv[i]);
		i++;
	}
	write(1, "\n", 1);
	return (OUT);
}

int	execution_env(t_ast *node, t_env_list *env)
{
	write(1, "\n", 1);
	if (node->argc > 1)
		write(1, "\nenv must be without any options or arguments", 45);
	else
		show_dict(&env);
	return (OUT);
}
