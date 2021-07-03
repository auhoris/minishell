#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/utils.h"
#include <stddef.h>

static void	lower_command_name(char *cmd)
{
	size_t	i;
	char	export[7];

	i = 0;
	while (cmd[i])
	{
		export[i] = ft_tolower(cmd[i]);
		i++;
	}
	if (ft_strcmp(export, "export") == 0)
		return ;
	i = 0;
	while (cmd[i])
	{
		cmd[i] = ft_tolower(cmd[i]);
		i++;
	}
}

static t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*node;

	node = init_node(NODE_SIMPLECOMMAND);
	if (node == NULL)
		return (ast_error_handler(node, ERROR_MALLOC));
	node->cmd_name = parser_get_args(parser);
	if (node->cmd_name == NULL)
		return (ast_error_handler(node, ERROR_MALLOC));
	if (ft_strcmp(node->cmd_name, "error_parser") == 0)
		return (ast_error_handler(node, ERROR_PARSER));
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF
		&& parser->cur_tok->e_type != TOKEN_PIPE)
	{
		parser_parse_agruments(node, parser);
		if (node->err_handler != OK)
			return (ast_error_handler(node, node->err_handler));
	}
	lower_command_name(node->cmd_name);
	return (node);
}

t_ast	*parser_parse_pipe(t_ast *left_node, t_parser *parser)
{
	t_ast	*pipe_node;

	pipe_node = init_node(NODE_PIPE);
	if (pipe_node == NULL)
		return (ast_error_handler(pipe_node, ERROR_MALLOC));
	pipe_node->table_value = ft_calloc(2, sizeof(t_ast *));
	if (pipe_node->table_value == NULL)
		return (ast_error_handler(pipe_node, ERROR_MALLOC));
	pipe_node->table_value[0] = left_node;
	if (parser_next_token(parser) == ERROR_PARSER)
		return (ast_error_handler(pipe_node, ERROR_PARSER));
	pipe_node->table_value[1] = parser_parse_command(parser);
	if (pipe_node->table_value[1]->err_handler != OK)
		return (ast_error_handler(pipe_node,
				pipe_node->table_value[1]->err_handler));
	return (pipe_node);
}

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*node;

	node = parser_parse_simple_command(parser);
	// node = NULL;
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF)
	{
		// printf("1\n");
		if (parser->cur_tok->e_type == TOKEN_PIPE)
		{
			// printf("2\n");
			return (parser_parse_pipe(node, parser));
		}
		// printf("3\n");
		node = parser_parse_simple_command(parser);
		if (node->err_handler != OK)
			return (ast_error_handler(node, node->err_handler));
	}
	return (node);
}

/* static int	make_table_value(t_ast *node, t_ast *simple_node)
{
	if (simple_node)
	{
		node->table_size++;
		node->table_value = ft_realloc(node->table_value,
				node->table_size * sizeof(t_ast *),
				(node->table_size - 1) * sizeof(t_ast *));
		if (node->table_value == NULL)
			return (ERROR_MALLOC);
		node->table_value[node->table_size - 1] = simple_node;
	}
	else
		return (ERROR_MALLOC);
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
		return (ast_error_handler(node, ERROR_MALLOC));
	node->table_size++;
	node->table_value[node->table_size - 1] = parser_parse_command(parser);
	if (node->table_value[node->table_size - 1]->err_handler != OK)
		return (ast_error_handler(node,
				node->table_value[node->table_size - 1]->err_handler));
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		if (parser_next_token(parser) == ERROR_PARSER)
			return (ast_error_handler(node, ERROR_PARSER));
		if (parser->cur_tok->e_type == TOKEN_EOF)
			break ;
		simple_node = parser_parse_command(parser);
		if (simple_node == NULL)
			return (ast_error_handler(node, ERROR_MALLOC));
		if (simple_node->err_handler != OK)
			return (ast_error_handler(node, node->err_handler));
		if (make_table_value(node, simple_node) != OK)
			return (ast_error_handler(node, ERROR_MALLOC));
	}
	return (node);
} */
