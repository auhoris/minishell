#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/ast.h"
# include "../includes/env.h"
# include "../includes/minishell.h"

int		check_builtin(t_exec *exec, t_ast *node, t_env_list *env);
int		get_pwd_dir(t_env_list *env, char **pwd_dir);
int		set_pwd_dir(t_env_list *env, char *pwd_dir);
int		set_old_pwd_dir(t_env_list *env, char *old_pwd_dir);
int		set_key_value(char *str, t_env_list *env);
void	execution_echo(t_exec *exec, t_ast *node);
int		execution_cd(t_exec *exec, t_ast *node, t_env_list *env);
int		execution_pwd(t_exec *exec, t_ast *node, t_env_list *env);
int		execution_export(t_ast *node, t_env_list *env);
int		execution_unset(t_ast *node, t_env_list **env);
int		executor_pipe(t_exec *exec, t_ast *node, t_env_list *env);
int		executor_simplecommand(t_exec *exec, t_ast *node, t_env_list *env);
int		unset_env_elem(t_env_list **env, char *key);
int		execution_env(t_exec *exec, t_ast *node, t_env_list *env);
char	**create_args(t_exec *exec, t_ast *node, int *error);
char	**create_env(t_env_list *env);
void	free_arr(char **arr);
void	clear_array(char **args, int index);
char	*search_bin(char *command);
int		set_redirection(t_exec *exec, t_ast *node);
int		restore_std(t_exec *exec, t_ast *node);
int		write_sort_env(t_env_list *env);

#endif
