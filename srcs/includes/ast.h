#ifndef AST_H
# define AST_H

# include <unistd.h>
# include "../../libs/libft/srcs/libft.h"

typedef struct s_ast
{
	enum
	{
		NODE_ROOT,
		NODE_PIPE,
		NODE_LREDIRECT,
		NODE_RREDIRECT,
		NODE_DOUBLE_REDIRECT,
		NODE_SIMPLECOMMAND,
		NODE_VARDEF,
		NODE_ERROR, // For bad nodes may be
	}	e_nodetype;
	char			*cmd_name;
	// Arguments
	size_t			argc;
	char			**argv;
	char			**flags;
	// Redirect
	char			*out_file;
	char			*in_file;
	char			*err_file;
	// Table
	struct s_ast	**table_value;
	size_t			table_size;
	// Vardef
	char			*var_name;
	char			*var_value;
}			t_ast;

t_ast	*init_node(int type);
void	free_nodes(t_ast *node);

#endif /* ifndef AST_H */
