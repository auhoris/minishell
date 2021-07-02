#include "includes/minishell.h"
#include "includes/exit_status.h"
#include "includes/parser.h"
#include "includes/token.h"
#include <stdlib.h>

static int		check_parser(t_parser *paser)
{
	int	type;

	if (paser == NULL)
		return (ERROR_MALLOC);
	type = paser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `;'", STDERR_FILENO);
		return (ERROR_PARSER);
	}
	if (type == TOKEN_PIPE)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `|'", STDERR_FILENO);
		return (ERROR_PARSER);
	}
	return (OK);
}

static int	wait_pids(t_exec *exec, int cnt)
{
	size_t	i;
	int		waiting;
	int		temp;
	int		ex_st;

	i = 0;
	ex_st = OK;
	if (exec->size_pids == 0)
		return (data_processing->ex_st);
	if (exec->n_flag != TRUE && cnt == 0)
		ft_putchar('\n');
	while (i < exec->size_pids)
	{
		temp = waitpid(exec->pids[i], &waiting, 0);
		if (WIFEXITED(waiting))
			ex_st = WEXITSTATUS(waiting);
		else
			if (WIFSIGNALED(waiting))
			{
				ex_st = ERROR_SIG_KILL + WTERMSIG(waiting);
				if (WTERMSIG(waiting) == 2)
					ft_putchar('\n');
			}
		i++;
	}
	data_processing->n_flag = TRUE;
	return (ex_st);
}

static int	exec_commands(t_data_processing *data_processing, t_parser *parser, size_t i)
{
	t_ast	*command;
	t_exec	*exec;
	int		out;

	out = OUT;
	command = parser_parse_command(parser);
	if (command == NULL)
		return (free_any(ERROR_MALLOC, command, free_root_parser));
	if (command->err_handler != OK)
		return (free_any(command->err_handler, command, free_root_parser));
	exec = init_exec(command);
	if (exec == NULL)
		return (free_any(ERROR_MALLOC, exec, free_exec));
	out = detour_tree(exec, command, data_processing->env);
	if (out == ERROR_EXIT)
		return (free_any(out, exec, free_exec));
	if (out == ERROR_BAD_COMMAND)
		return (free_any(ERROR_BAD_COMMAND, exec, free_exec));
	data_processing->ex_st = wait_pids(exec, i);
	// printf("data_processing->ex_st = %d\n", data_processing->ex_st);
	free_exec(exec);
	return (out);
}
/* if (out == ERROR_EXIT && data_processing->ex_st != OK)
	return (free_any(data_processing->ex_st, exec, free_exec)); */

/* command = parser_parse_command(parser);
if (command == NULL)
	return (free_any(ERROR_MALLOC, command, free_root_parser));
if (command->err_handler != OK)
	return (free_any(command->err_handler, command, free_root_parser));
exec = init_exec(command);
if (exec == NULL)
	return (free_any(ERROR_MALLOC, exec, free_exec));
out = detour_tree(exec, command, data_processing->env);
if (out == ERROR_EXIT)
	return (free_any(out, exec, free_exec));
wait_pids(exec, i);
free_exec(exec); */
static int	start_loop(t_data_processing *data_processing, t_parser *parser)
{
	int		out;
	// int		i;

	data_processing->cmd_i = 0;
	out = OUT;
	out = exec_commands(data_processing, parser, data_processing->cmd_i);
	if (out == ERROR_MALLOC || out == ERROR_EXIT || out == ERROR_PARSER)
		return (out);
	data_processing->cmd_i++;
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		if (parser_next_token(parser) == ERROR_PARSER)
			return (EXIT_PARSER);
		if (parser->cur_tok->e_type == TOKEN_EOF)
			break ;
		out = exec_commands(data_processing, parser, data_processing->cmd_i);
		if (out == ERROR_MALLOC || out == ERROR_EXIT || out == ERROR_PARSER)
			return (out);
		data_processing->cmd_i++;
	}
	return (out);
}

/* data_processing->size_pids = exec->size_pids;
data_processing->flag_echo = exec->flag_echo; */

//================================================

/* root = parser_parse_commands(parser);
free_parser(parser);
if (root->err_handler != OK)
	return (free_any(root->err_handler, root, free_root_parser));
exec = init_exec(root);
if (exec == NULL)
	return (free_any(ERROR_MALLOC, exec, free_exec));
out = detour_tree(exec, root, data_processing->env);
data_processing->size_pids = exec->size_pids;
data_processing->flag_echo = exec->flag_echo;
free_exec(exec); */

int	start_parsing(t_data_processing *data_processing)
{
	t_lexer		*lexer;
	t_parser	*parser;
	int			out;
	int			check;

	out = OK;
	lexer = init_lexer(data_processing->actual_history->prev->command);
	parser = init_parser(lexer, data_processing->env);
	check = check_parser(parser);
	if (check != OK)
	{
		data_processing->ex_st = EXIT_PARSER;
		return (free_any(check, parser, free_parser));
	}
	out = start_loop(data_processing, parser);
	if (out == ERROR_PARSER && data_processing->ex_st != 1)
		data_processing->ex_st = ERROR_PARSER;
	free_parser(parser);
	return (out);
}
