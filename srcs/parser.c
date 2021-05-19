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
	parser->current_token = lexer_get_next_token(lexer);
	return (parser);
}

void	parser_next_token(t_parser *parser)
{
	parser->prev_token = parser->current_token;
	parser->current_token = lexer_get_next_token(parser->lexer);
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
	table->table_value[table->table_size] = parser_parse_simple_command(parser);
	table->table_size++;
	while (parser->current_token->e_type == TOKEN_SEMI)
	{
		table->table_value[table->table_size - 1]->e_nodetype = NODE_SEQUENCE;
		parser_next_token(parser);
		scmd = parser_parse_simple_command(parser);
		if (scmd)
		{
			table->table_size++;
			table->table_value = ft_realloc(table->table_value, table->table_size * sizeof(t_ast *), (table->table_size - 1) * sizeof(t_ast *));
			table->table_value[table->table_size - 1] = scmd;
		}

	}
	return (table);
}

void	print_token(t_token *token)
{
	printf("type='%d'\tvalue='%s'\n", token->e_type, token->value);
}

t_ast	*parser_parse_pipe(t_ast *left_node, t_parser *parser)
{
	t_ast	*pipe_node;

	pipe_node = init_node(NODE_PIPE);
	pipe_node->table_value = ft_calloc(2, sizeof(t_ast *));
	pipe_node->table_value[0] = left_node;
	parser_next_token(parser);
	pipe_node->table_value[1] = parser_parse_simple_command(parser);
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

t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*scmd;

	scmd = init_node(NODE_SIMPLECOMMAND);
	scmd->cmd_name = ft_strdup(parser->current_token->value);
	parser_next_token(parser);
	while (parser->current_token->e_type != TOKEN_SEMI
		&& parser->current_token->e_type != TOKEN_EOF)
	{
		if (parser->current_token->e_type == TOKEN_PIPE)
			return (parser_parse_pipe(scmd, parser));
		else if (parser->current_token->e_type == TOKEN_MORE)
			return (parser_parse_redirect(scmd, parser, NODE_RREDIRECT));
		else if (parser->current_token->e_type == TOKEN_LESS)
			return (parser_parse_redirect(scmd, parser, NODE_LREDIRECT));
		else if (parser->current_token->e_type == TOKEN_DMORE)
			return (parser_parse_redirect(scmd, parser, NODE_DOUBLE_REDIRECT));
		scmd->argc++;
		scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
							(scmd->argc - 1) * sizeof(*scmd->argv));
		scmd->argv[scmd->argc - 1] = ft_strdup(parser->current_token->value);
		parser_next_token(parser);
	}
	return (scmd);
}
