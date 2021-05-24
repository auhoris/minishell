#ifndef MINISHELL_H
# define MINISHELL_H

#include "env.h"

int		termcap(t_env_dict **env);
int		check_input_params(int argc, char **argv);
//	Дефайны
# define TRUE 1
# define FALSE 0
//	Инклюды
# include <stdio.h>
# include <stdlib.h>

#endif /* ifndef MINISHELL_H */
