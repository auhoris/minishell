#include "includes/minishell.h"
#include "includes/exit_status.h"
#include "includes/parser.h"

static int		check_parser(t_parser *paser)
{
	int	type;

	if (paser == NULL)
		return (ERROR_MALLOC);
	type = paser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `;'\n", STDERR_FILENO);
		return (ERROR_PARSER);
	}
	if (type == TOKEN_PIPE)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
		return (ERROR_PARSER);
	}
	return (OK);
}

static int	wait_pids(t_exec *exec, int cnt)
{
	size_t	i;
	int		waiting;
	int		temp;
	int		exit_status;

	i = 0;
	if (exec->size_pids == 0)
		return (OK);
	if (cnt == 0)
		ft_putchar('\n');
	while (i < exec->size_pids)
	{
		// printf("here\n");
		temp = waitpid(exec->pids[i], &waiting, 0);
		// printf("temp = %d\n", temp);
		if ((temp = WIFEXITED(waiting)))
		{
			// printf("g_exst = %d\n", g_exst);
			exit_status = WEXITSTATUS(waiting);
			// printf("exit_status = %d\n", exit_status);
			// printf("g_exst = %d\n", g_exst);
		}
		i++;
	}
	// printf("exit_status = %d\n", exit_status);
	return (exit_status);
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
	if (out != OK)
		return (out);
	if (out == ERROR_EXIT)
		return (free_any(out, exec, free_exec));
	if (out == ERROR_BAD_COMMAND)
		return (free_any(EXIT_NOT_FOUND, exec, free_exec));
	out = wait_pids(exec, i);
	free_exec(exec);
	return (out);
}

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
	int		i;

	i = 0;
	out = OUT;
	out = exec_commands(data_processing, parser, i);
	if (out == ERROR_MALLOC || out == ERROR_EXIT)
		return (out);
	if (out == ERROR_PARSER)
		return (EXIT_PARSER);
	i++;
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		if (parser_next_token(parser) == ERROR_PARSER)
			return (EXIT_PARSER);
		if (parser->cur_tok->e_type == TOKEN_EOF)
			break ;
		out = exec_commands(data_processing, parser, i);
		if (out == ERROR_MALLOC || out == ERROR_EXIT)
			return (out);
		if (out == ERROR_PARSER)
			return (EXIT_PARSER);
		i++;
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

	lexer = init_lexer(data_processing->actual_history->prev->command);
	parser = init_parser(lexer, data_processing->env);
	check = check_parser(parser);
	if (check != OK)
	{
		g_exst = EXIT_PARSER;
		return (free_any(check, parser, free_parser));
	}
	// printf("g_exst = %d\n", g_exst);
	out = start_loop(data_processing, parser);
	g_exst = out;
	free_parser(parser);
	return (out);
}
