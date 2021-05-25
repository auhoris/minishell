#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/ast.h"
# include "../includes/env.h"

int	check_builtin(t_ast *node, t_env_list *env);
int	get_pwd_dir(t_env_list *env, char **pwd_dir);
int	set_pwd_dir(t_env_list *env, char *pwd_dir);

#endif