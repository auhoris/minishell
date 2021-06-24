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
	size_t			argc;
	char			**argv;
	int				fd_in;
	int				fd_out;
	struct s_ast	**table_value;
	size_t			table_size;
	char			*var_name;
	char			*var_value;
	int				err_handler;
}			t_ast;

t_ast	*init_node(int type);
void	free_nodes(t_ast *node);
t_ast	*ast_error_handler(t_ast *node, int code);
// t_ast	*ast_error_handler(t_ast *node);

#endif /* ifndef AST_H */
