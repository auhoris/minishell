#include "../includes/ast.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "../includes/minishell.h"

void	write_cd(t_ast *node)
{
	g_data_processing->ex_st = ERROR_NOT_EXIST;
	write(1, "\nminishell: cd: ", 16);
	write(1, node->argv[0], ft_strlen(node->argv[0]));
	write(1, ": ", 2);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
}
