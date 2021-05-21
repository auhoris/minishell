#ifndef AST_H
# define AST_H

# include <unistd.h>
# include "../../libs/libft/srcs/libft.h"

typedef struct s_args
{
	size_t	number_of_agrs;
	char	**args_value;
	char	**flags;
}			t_args;

typedef struct s_ast
{
	enum
	{
		NODE_ROOT, //0
		NODE_PIPE, //1
		NODE_LREDIRECT, //2
		NODE_RREDIRECT, //3
		NODE_DOUBLE_REDIRECT, //4
		NODE_SIMPLECOMMAND, //5
		NODE_VARDEF, //6
	}	e_nodetype;
	char			*cmd_name;
	//				Arguments
	size_t			argc;
	char			**argv;
	char			**flags;
	//				Table
	struct s_ast	**table_value;
	size_t			table_size;
	char			*var_name;
	char			*var_value;
}			t_ast;

t_ast	*init_node(int type);

#endif /* ifndef AST_H */
