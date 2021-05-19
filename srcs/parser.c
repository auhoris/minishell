#include "includes/parser.h"
#include "includes/lexer.h"
#include "includes/ast.h"
#include <stdio.h>
#include <stdlib.h>

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->cur_tok = lexer_get_next_token(lexer);
	return (parser);
}

void	parser_next_token(t_parser *parser)
{
	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	destroy_token(parser->prev_token);
}

t_ast	*parser_parse_commands(t_parser *parser)
{
	t_ast	*table;
	t_ast	*scmd;

	table = init_node(NODE_ROOT);
	table->table_value = ft_calloc(1, sizeof(t_ast *));
	if (table->table_value == NULL)
		return (NULL);
	table->table_value[table->table_size] = parser_parse_command(parser);
	table->table_size++;
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		parser_next_token(parser);
		scmd = parser_parse_command(parser);
		if (scmd)
		{
			table->table_size++;
			table->table_value = ft_realloc(table->table_value, table->table_size * sizeof(t_ast *), (table->table_size - 1) * sizeof(t_ast *));
			table->table_value[table->table_size - 1] = scmd;
		}

	}
	return (table);
}

t_ast	*parser_parse_pipe(t_ast *left_node, t_parser *parser)
{
	t_ast	*pipe_node;

	pipe_node = init_node(NODE_PIPE);
	pipe_node->table_value = ft_calloc(2, sizeof(t_ast *));
	pipe_node->table_value[0] = left_node;
	parser_next_token(parser);
	pipe_node->table_value[1] = parser_parse_command(parser);
	return (pipe_node);
}

t_ast	*parser_parse_redirect(t_ast *left_node, t_parser *parser, int type)
{
	t_ast	*redirect;

	redirect = init_node(type);
	redirect->table_value = ft_calloc(2, sizeof(t_ast *));
	redirect->table_value[0] = left_node;
	parser_next_token(parser);
	redirect->table_value[1] = parser_parse_simple_command(parser);
	return (redirect);
}

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*command;

	command = init_node(NODE_SIMPLECOMMAND);
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF)
	{
		if (parser->cur_tok->e_type == TOKEN_PIPE)
			return (parser_parse_pipe(command, parser));
		command = parser_parse_simple_command(parser);
	}
	return (command);
}

void	parser_parse_agruments(t_ast *scmd, t_parser *parser)
{
	scmd->argc++;
	scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
						(scmd->argc - 1) * sizeof(*scmd->argv));
	scmd->argv[scmd->argc - 1] = ft_strdup(parser->cur_tok->value);
	parser_next_token(parser);
}

t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*scmd;

	scmd = init_node(NODE_SIMPLECOMMAND);
	scmd->cmd_name = ft_strdup(parser->cur_tok->value);
	parser_next_token(parser);
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF
		&& parser->cur_tok->e_type != TOKEN_PIPE)
	{
		if (parser->cur_tok->e_type == TOKEN_MORE || parser->cur_tok->e_type == TOKEN_LESS
				|| parser->cur_tok->e_type == TOKEN_DMORE)
			return (parser_parse_redirect(scmd, parser, parser->cur_tok->e_type));
		parser_parse_agruments(scmd, parser);
	}
	return (scmd);
}
