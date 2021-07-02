#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "../includes/exit_status.h"
#include "executor.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

void	handle_echo_output(t_exec *exec, t_ast *node,
		size_t pos, size_t n_flag, size_t d_flag)
{
	// printf("%zu: this ---- > %s\n", pos, node->argv[pos]);
	(void)exec;
	(void)n_flag;
	if (ft_strcmp(node->argv[pos], "") == 0)
		return ;
	if (pos != n_flag + d_flag)
		ft_putchar(' ');
	ft_putstr(node->argv[pos]);
}

void	execution_echo(t_exec *exec, t_ast *node)
{
	size_t	i;
	int		n_flag;
	int		d_flag;

	exec->n_flag = TRUE;
	n_flag = 0;
	i = 0;
	d_flag = 0;
	if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	while (i < node->argc && ft_strcmp(node->argv[i], "-n") == 0)
		i++;
	n_flag = i;
	while (i < node->argc && ft_strcmp(node->argv[i], "") == 0)
		i++;
	d_flag = i - n_flag;
	while (i < node->argc)
	{
		handle_echo_output(exec, node, i, n_flag, d_flag);
		i++;
	}
	if (!n_flag)
		ft_putchar('\n');
	data_processing->ex_st = OK;
}

int	execution_cd(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	char	pwd_dir[256];

	(void)exec;
	exec->n_flag = TRUE;
	data_processing->n_flag = FALSE;
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
		ft_putchar('\n');
		return (EXIT_NOT_EXIST);
	}
	else
		if (set_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	return (OUT);
}

int	execution_pwd(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	char	*pwd_dir;

	exec->n_flag = TRUE;
	if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	pwd_dir = NULL;
	out = get_pwd_dir(env, &pwd_dir);
	if (out == OUT)
	{
		ft_putstr(pwd_dir);
		ft_putstr("\n");
	}
	return (out);
}

int	execution_export(t_exec *exec, t_ast *node, t_env_list *env)
{
	size_t	i;
	int		out;

	exec->n_flag = TRUE;
	if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	i = 0;
	if (node->argc == 0)
	{
		write_sort_env(env);
		return (OUT);
	}
	while (i < node->argc)
	{
		out = set_key_value(node->argv[i], env);
		if (out == ERROR_MALLOC)
			return (ERROR_MALLOC);
		i++;
	}
	return (OUT);
}

int	execution_unset(t_exec *exec, t_ast *node, t_env_list **env)
{
	size_t		i;

	(void)exec;
	/* if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE; */
	/* if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1); */
	data_processing->n_flag = FALSE;
	if (!(*env))
		return (OUT);
	i = 0;
	while (i < node->argc)
	{
		unset_env_elem(env, node->argv[i]);
		i++;
	}
	return (OUT);
}

int	execution_env(t_exec *exec, t_ast *node, t_env_list *env)
{
	exec->n_flag = TRUE;
	if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	if (node->argc > 1)
	{
		write(1, "\nenv must be without any options or arguments", 45);
		return (ERROR_NOT_EXIST );
	}
	else
		show_dict(&env);
	ft_putchar('\n');
	return (OUT);
}
