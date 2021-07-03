#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "../includes/exit_status.h"
#include "executor.h"
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

static void	handle_echo_output(t_ast *node,
		size_t pos, size_t n_flag, size_t d_flag)
{
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
	/* if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		g_data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1); */
	while (i < node->argc && ft_strcmp(node->argv[i], "-n") == 0)
		i++;
	n_flag = i;
	while (i < node->argc && ft_strcmp(node->argv[i], "") == 0)
		i++;
	d_flag = i - n_flag;
	while (i < node->argc)
		handle_echo_output(node, i++, n_flag, d_flag);
	if (!n_flag)
		ft_putchar('\n');
	g_data_processing->n_state = FALSE;
	g_data_processing->ex_st = OK;
}

int	execution_cd(t_exec *exec, t_ast *node, t_env_list *env)
{
	int		out;
	char	pwd_dir[256];

	exec->n_flag = TRUE;
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
		write_cd(node);
		return (OK);
	}
	else
		if (set_pwd_dir(env, pwd_dir) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	return (OUT);
}

int	execution_pwd(t_exec *exec, t_ast *node)
{
	char	pwd_dir[256];

	(void)node;
	exec->n_flag = TRUE;
	/* if (exec->pipewrite != STDOUT_FILENO || node->fd_out != STDOUT_FILENO)
		g_data_processing->n_flag = FALSE;
	if (exec->pipewrite == STDOUT_FILENO && node->fd_out == STDOUT_FILENO)
		write (exec->tempout, "\n", 1); */
	if (getcwd(pwd_dir, 256) == NULL)
		return (ERROR_MALLOC);
	ft_putstr(pwd_dir);
	ft_putstr("\n");
	return (OUT);
}
