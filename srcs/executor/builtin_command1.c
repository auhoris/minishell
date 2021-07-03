#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"
#include <stddef.h>
#include <unistd.h>

int	execution_export(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		i;
	int		out;
	int		err_cnt;

	err_cnt = 0;
	exec->n_flag = TRUE;
	if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1);
	if (node->argc == 0)
	{
		write_sort_env(env);
		return (OUT);
	}
	i = -1;
	while ((size_t)++i < node->argc)
	{
		out = set_key_value(node->argv[i], env, err_cnt);
		if (out == ERROR)
			err_cnt++;
		if (out == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

int	execution_unset(t_exec *exec, t_ast *node, t_env_list **env)
{
	size_t		i;

	(void)exec;
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
		return (ERROR_NOT_EXIST);
	}
	else
		show_dict(&env);
	ft_putchar('\n');
	return (OUT);
}
