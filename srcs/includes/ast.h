#ifndef AST_H
# define AST_H

# include <unistd.h>
# include "../../libs/libft/srcs/libft.h"

// Мб добавить fd для in_file & out_file
typedef struct s_ast
{
	enum
	{
		NODE_ROOT,
		NODE_PIPE,
		NODE_SIMPLECOMMAND,
		NODE_VARDEF,
		NODE_ERROR,
	}	e_nodetype;
	char			*cmd_name;
	// Arguments
	size_t			argc;
	char			**argv;
	// Redirect
	int				fd_in;
	int				fd_out;
	// Table
	struct s_ast	**table_value;
	size_t			table_size;
	// Vardef
	char			*var_name;
	char			*var_value;
	// Error handling
	int				err_handler;
}			t_ast;

t_ast	*init_node(int type);
void	free_nodes(t_ast *node);
t_ast	*ast_error_handler(t_ast *node);

#endif /* ifndef AST_H */
