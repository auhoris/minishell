#include "includes/ast.h"
#include "includes/parser.h"
#include "includes/exit_status.h"
#include <errno.h>

int	make_node_fd(char *filename, int type, t_ast *node)
{
	if (type == TOKEN_MORE || type == TOKEN_DMORE)
	{
		if (type == TOKEN_MORE)
			node->fd_out = open(filename, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU);
		else
			node->fd_out = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	}
	else
		node->fd_in = open(filename, O_RDONLY);
	if (node->fd_out == -1 || node->fd_in == -1)
	{
		if (errno == ENOENT)
			data_processing->ex_st = EXIT_NOT_EXIST;
		else if (errno == EACCES)
			data_processing->ex_st = ERROR_PERM_DENIED;
		ft_putchar('\n');
		perror(filename);
		data_processing->n_flag =  TRUE;
		return (ERROR_PARSER);
	}
	return (OK);
}

void	check_fd(t_ast *node, int type)
{
	if (type == TOKEN_MORE || type == TOKEN_DMORE)
	{
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
	}
	else if (type == TOKEN_LESS)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
	}
}
