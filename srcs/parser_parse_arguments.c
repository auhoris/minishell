#include "includes/env.h"
#include "includes/errors.h"
#include "includes/parser.h"
#include "includes/exit_status.h"
#include "includes/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#define AMBIG 95

static int	handle_redirect_loop(t_parser *parser, t_ast *node)
{
	int		prev_type;
	int		curr_type;
	char	*file;

	prev_type = parser->cur_tok->e_type;
	while (prev_type == TOKEN_MORE || prev_type == TOKEN_LESS
		|| prev_type == TOKEN_DMORE)
	{
		curr_type = parser_next_token(parser);
		if (curr_type == TOKEN_PIPE || curr_type == TOKEN_SEMI)
			return (ERROR_PARSER);
		if (curr_type == ERROR_PARSER || curr_type == TOKEN_DOLLAR)
			return (ERROR_PARSER);
		file = parser_get_args(parser);
		if (ft_strcmp(file, "error_parser") == 0)
			return (ERROR_PARSER);
		if (make_node_fd(file, prev_type, node) != OK)
			return (ERROR_PARSER);
		prev_type = parser->cur_tok->e_type;
		if (prev_type == ERROR_PARSER)
			return (ERROR_PARSER);
		check_fd(node, prev_type);
	}
	return (OK);
}
/* int		prev_type;
int		curr_type;
char	*file;

prev_type = parser->cur_tok->e_type;
while (prev_type == TOKEN_MORE || prev_type == TOKEN_LESS
	|| prev_type == TOKEN_DMORE)
{
	curr_type = parser_next_token(parser);
	if (curr_type == TOKEN_PIPE || curr_type == TOKEN_SEMI)
		return (ERROR_PARSER);
	if (curr_type == ERROR_PARSER || curr_type == TOKEN_DOLLAR)
		return (ERROR_PARSER);
	file = parser_get_args(parser);
	if (ft_strcmp(file, "error_parser") == 0)
		return (ERROR_PARSER);
	if (make_node_fd(file, prev_type, node) != OK)
		return (ERROR_PARSER);
	prev_type = parser->cur_tok->e_type;
	if (prev_type == ERROR_PARSER)
		return (ERROR_PARSER);
	check_fd(node, prev_type);
} */

static int	parser_parse_redirect(t_parser *parser, t_ast *node)
{
	int	err;

	err = handle_redirect_loop(parser, node);
	if (err != OK)
		return (ERROR_PARSER);
	if (ft_strcmp(node->cmd_name, "") == 0)
	{
		node->cmd_name = parser_get_args(parser);
		if (node->cmd_name == NULL)
			return (ERROR_MALLOC);
		if (ft_strcmp(node->cmd_name, "error_parser") == 0)
			return (ERROR_PARSER);
	}
	return (OK);
}

t_ast	*parser_parse_agruments(t_ast *node, t_parser *parser)
{
	if (parser->cur_tok->e_type == TOKEN_MORE
		|| parser->cur_tok->e_type == TOKEN_LESS
		|| parser->cur_tok->e_type == TOKEN_DMORE)
	{
		node->err_handler = parser_parse_redirect(parser, node);
		if (node->err_handler != OK)
			return (ast_error_handler(node, node->err_handler));
	}
	else
	{
		node->argc++;
		node->argv = ft_realloc(node->argv, node->argc * sizeof(*node->argv),
				(node->argc - 1) * sizeof(*node->argv));
		if (node->argv == NULL)
			return (ast_error_handler(node, ERROR_MALLOC));
		node->argv[node->argc - 1] = parser_get_args(parser);
		if (node->argv[node->argc - 1] == NULL)
			return (ast_error_handler(node, ERROR_MALLOC));
		else if (ft_strcmp(node->argv[node->argc - 1], "error_parser") == 0)
			return (ast_error_handler(node, ERROR_PARSER));
	}
	return (node);
}
