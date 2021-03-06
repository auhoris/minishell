#ifndef MINISHELL_H
# define MINISHELL_H

//	Инклюды
# include "env.h"
# include "ast.h"
# include "types.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/_types/_size_t.h>

//	Дефайны
# define TRUE 1
# define FALSE 0

typedef struct s_exec
{
	t_ast	*root;
	t_ast	*node;
	int		curr_node_type;
	int		tempin;
	int		tempout;
	int		exit_status;
	int		is_redir;
	int		*pids;
	size_t	size_pids;
	int		piperead;
	int		pipewrite;
	size_t	i;
	int		n_flag;
}			t_exec;

t_data_processing	*g_data_processing;
t_exec	*init_exec(t_ast *root);
int		termcap(t_env_list *env);
void	handler(int s);
int		check_input_params(int argc, char **argv);
int		detour_tree(t_exec *exec, t_ast *node, t_env_list *env);
int		start_parsing(t_data_processing *data_processing);
void	free_lexer(t_lexer *lexer);
void	free_parser(void *parser);
void	free_root_parser(void *root);
void	free_exec(void *exec);
int		free_any(int code, void *content, void(*del)(void *));
int		executor_exit(size_t argc, char **argv, t_env_list **env);
int		advance_shlvl(t_env_list **env);
void	test(void);

#endif /* ifndef MINISHELL_H */
