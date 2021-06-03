#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/utils.h"

static t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*node;

	node = init_node(NODE_SIMPLECOMMAND);
	if (node == NULL)
		return (ast_error_handler(node));
	node->cmd_name = parser_get_args(parser);
	if (node->cmd_name == NULL)
		return (ast_error_handler(node));
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF
		&& parser->cur_tok->e_type != TOKEN_PIPE)
	{
		parser_parse_agruments(node, parser);
		if (node->err_handler == ERROR)
			return (ast_error_handler(node));
	}
	return (node);
}

t_ast	*parser_parse_pipe(t_ast *left_node, t_parser *parser)
{
	t_ast	*pipe_node;

	pipe_node = init_node(NODE_PIPE);
	if (pipe_node == NULL)
		return (ast_error_handler(pipe_node));
	pipe_node->table_value = ft_calloc(2, sizeof(t_ast *));
	if (pipe_node->table_value == NULL)
		return (ast_error_handler(pipe_node));
	pipe_node->table_value[0] = left_node;
	if (parser_next_token(parser) == ERROR)
		return (ast_error_handler(pipe_node));
	pipe_node->table_value[1] = parser_parse_command(parser);
	if (pipe_node->table_value[1]->err_handler != OK)
		return (ast_error_handler(pipe_node));
	return (pipe_node);
}

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*node;

	node = NULL;
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF)
	{
		if (parser->cur_tok->e_type == TOKEN_PIPE)
			return (parser_parse_pipe(node, parser));
		node = parser_parse_simple_command(parser);
		if (node->err_handler != OK)
			return (ast_error_handler(node));
	}
	return (node);
}

static int	make_table_value(t_ast *node, t_ast *simple_node)
{
	if (simple_node)
	{
		node->table_size++;
		node->table_value = ft_realloc(node->table_value,
				node->table_size * sizeof(t_ast *),
				(node->table_size - 1) * sizeof(t_ast *));
		if (node->table_value == NULL)
			return (ERROR);
		node->table_value[node->table_size - 1] = simple_node;
	}
	else
	{
		return (ERROR);
	}
	return (OK);
}

t_ast	*parser_parse_commands(t_parser *parser)
{
	t_ast	*node;
	t_ast	*simple_node;

	node = init_node(NODE_ROOT);
	if (node == NULL)
		return (NULL);
	node->table_value = ft_calloc(1, sizeof(t_ast *));
	if (node->table_value == NULL)
		return (ast_error_handler(node));
	node->table_size++;
	node->table_value[node->table_size - 1] = parser_parse_command(parser);
	if (node->table_value[node->table_size - 1]->err_handler != OK)
		return (ast_error_handler(node));
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		if (parser_next_token(parser) == ERROR)
			return (ast_error_handler(node));
		simple_node = parser_parse_command(parser);
		if (make_table_value(node, simple_node) == ERROR)
			return (ast_error_handler(node));
	}
	return (node);
}
