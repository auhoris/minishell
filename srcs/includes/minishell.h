#ifndef MINISHELL_H
# define MINISHELL_H

//	Инклюды
# include "env.h"
# include "ast.h"
# include <stdio.h>
# include <stdlib.h>

//	Дефайны
# define TRUE 1
# define FALSE 0

typedef struct s_exec
{
	t_ast	*root;
	// Мб будет полезно
	t_ast	*node;
	int		curr_node_type;
	//
	size_t	pipes; // ??
	int		tempin;
	int		tempout;
	int		exit_status;
	int		fd[2];
	int		r_or_w;
}		t_exec;

t_exec	*init_exec(t_ast *root, size_t pipes);
int		termcap(t_env_list *env);
int		check_input_params(int argc, char **argv);
int		detour_tree(t_exec *exec, t_ast *node, t_env_list *env);

#endif /* ifndef MINISHELL_H */
