#include "../includes/minishell.h"
#include "../includes/types.h"

void	isredir(t_exec *exec)
{
	if (!exec->is_redir)
	{
		dup2(exec->piperead, STDIN_FILENO);
		dup2(exec->pipewrite, STDOUT_FILENO);
		if (exec->piperead != STDIN_FILENO)
			close(exec->piperead);
		if (exec->pipewrite != STDOUT_FILENO)
			close(exec->pipewrite);
	}
}
