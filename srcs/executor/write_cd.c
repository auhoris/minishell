#include "../includes/ast.h"
#include <errno.h>
#include <unistd.h>
#include <string.h>

void	write_cd(t_ast *node)
{
	write(1, "\nminishell: cd: ", 16);
	write(1, node->argv[0], ft_strlen(node->argv[0]));
	write(1, ": ", 2);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	ft_putchar('\n');
}
