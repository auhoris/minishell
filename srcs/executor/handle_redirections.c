#include "../includes/minishell.h"

int	set_redirection(t_exec *exec, t_ast *node)
{
	// printf("set_redirection = %p\n", node);
	exec->tempin = dup(STDIN_FILENO);
	exec->tempout = dup(STDOUT_FILENO);
	if (exec->piperead != STDIN_FILENO)
		dup2(exec->piperead, STDIN_FILENO);
	if (exec->pipewrite != STDOUT_FILENO)
		dup2(exec->pipewrite, STDOUT_FILENO);
	if (node->fd_in != STDIN_FILENO || node->fd_out != STDOUT_FILENO)
	{
		exec->is_redir = 1;
		if (node->fd_in != STDIN_FILENO)
		{
			dup2(node->fd_in, STDIN_FILENO);
			close(node->fd_in);
		}
		if (node->fd_out != STDOUT_FILENO)
		{
			dup2(node->fd_out, STDOUT_FILENO);
			close(node->fd_out);
		}
	}
	return (OK);
}

int	restore_std(t_exec *exec, t_ast *node)
{
	if (exec->piperead != STDIN_FILENO)
		dup2(exec->tempin, STDIN_FILENO);
	if (exec->pipewrite != STDOUT_FILENO)
		dup2(exec->tempout, STDOUT_FILENO);
	if (node->fd_in != STDIN_FILENO)
		dup2(exec->tempin, STDIN_FILENO);
	if (node->fd_out != STDOUT_FILENO)
		dup2(exec->tempout, STDOUT_FILENO);
	close(exec->tempout);
	close(exec->tempin);
	return (OK);
}
