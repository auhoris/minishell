#ifndef MINISHELL_H
# define MINISHELL_H

//	Инклюды
# include "env.h"
# include <stdio.h>
# include <stdlib.h>

//	Дефайны
# define TRUE 1
# define FALSE 0

int		termcap(t_env_list *env);
int		check_input_params(int argc, char **argv);

#endif /* ifndef MINISHELL_H */
