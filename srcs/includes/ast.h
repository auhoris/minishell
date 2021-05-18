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
		AST_TABLE,
		AST_EMPTY,
		AST_SIMPLECMD,
		AST_PIPE_IN,
		AST_PIPE_OUT,
		AST_REDIR_IN,
		AST_REDIR_OUT,
		AST_LAST_NODE,
	}	e_nodetype;
	char			*cmd_name;
	//				Arguments
	size_t			argc;
	char			**argv;
	char			**flags;
	//				Pipes and redirect
	int				fd_pipe_read;
	int				fd_pipe_write;
	char			*redirect_in;
	char			*redirect_out;
	//				Table
	struct s_ast	**table_value;
	size_t			table_size;
}			t_ast;

t_ast	*init_node(int type);

#endif /* ifndef AST_H */
