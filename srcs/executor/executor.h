#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../includes/ast.h"
# include "../includes/env.h"
# include "../includes/minishell.h"

int		check_builtin(t_exec *exec, t_ast *node, t_env_list *env);
int		get_pwd_dir(t_env_list *env, char **pwd_dir);
int		set_pwd_dir(t_env_list *env, char *pwd_dir);
int		set_old_pwd_dir(t_env_list *env, char *old_pwd_dir);
int		set_key_value(char *str, t_env_list *env, int pos);
void	execution_echo(t_exec *exec, t_ast *node);
int		execution_cd(t_exec *exec, t_ast *node, t_env_list *env);
int		execution_pwd(t_exec *exec, t_ast *node);
int		execution_export(t_exec *exec, t_ast *node, t_env_list *env);
int		execution_unset(t_exec *exec, t_ast *node, t_env_list **env);
int		executor_pipe(t_exec *exec, t_ast *node, t_env_list *env);
int		executor_simplecommand(t_exec *exec, t_ast *node, t_env_list *env);
int		unset_env_elem(t_env_list **env, char *key);
int		execution_env(t_exec *exec, t_ast *node, t_env_list *env);
char	**create_args(t_ast *node, int *error, char **path_array);
char	**create_env(t_env_list *env);
void	free_arr(char **arr, char **env_array);
void	clear_array(char **args, int index);
int		search_bin(char **bin_command, char *command, char **path_array);
int		set_redirection(t_exec *exec, t_ast *node);
int		restore_std(t_exec *exec, t_ast *node);
int		write_sort_env(t_env_list *env);
int		get_path_array(t_env_list *env, char ***bin_arr);
void	write_cd(t_ast *node);
void	isredir(t_exec *exec);
int		fill_args(char **args, t_ast *node);
int		check_key_value_repeated(char *key, char *value, t_env_list *env);
int		get_key_export(char *str, char **key, int *i);
int		get_value_export(char *str, char **value, int *i);
void	value_key_free(char *value, char *key, t_env_list *new);
void	write_export(t_env_list *env, int last);
int		create_new_env(char *key, char *value, t_env_list *env);

#endif
