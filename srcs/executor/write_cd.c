#include "../includes/ast.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "../includes/minishell.h"

void	write_cd(t_ast *node)
{
	g_data_processing->ex_st = ERROR_NOT_EXIST;
	write(STDERR_FILENO, "minishell: cd: ", 16);
	write(STDERR_FILENO, node->argv[0], ft_strlen(node->argv[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
	ft_putchar_fd('\n', STDERR_FILENO);
	g_data_processing->n_state = FALSE;
}
