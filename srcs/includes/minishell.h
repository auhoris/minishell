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

int		termcap(t_env_list *env);
int		check_input_params(int argc, char **argv);
int		detour_tree(t_ast *node, t_env_list *env);

#endif /* ifndef MINISHELL_H */
