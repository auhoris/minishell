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

void	parser_expect(t_parser *parser, int type)
{
	if ((int)parser->current_token->e_type != type)
	{
		printf("[Parser]: Unexpected token '%d', with value '%s'\n",
				parser->current_token->e_type, parser->current_token->value);
		exit(1);
	}
	parser->prev_token = parser->current_token;
	parser->current_token = lexer_get_next_token(parser->lexer);
}

void	parser_get_next_token(t_parser *parser)
{
	parser->prev_token = parser->current_token;
	parser->current_token = lexer_get_next_token(parser->lexer);
}

t_ast	*parser_parse_commands(t_parser *parser)
{
	t_ast	*table;
	t_ast	*scmd;

	table = init_node(AST_TABLE);
	table->table_value = ft_calloc(1, sizeof(t_ast *));
	if (table->table_value == NULL)
		return (NULL);
	table->table_value[table->table_size] = parser_parse_command(parser);
	table->table_size++;
	while (parser->current_token->e_type == TOKEN_SEMI)
	{
		parser_get_next_token(parser);
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

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*scmd;

	scmd = init_node(AST_SIMPLECMD);
	if (parser->current_token->e_type == BAD_TOKEN)
	{
		printf("Unexpected token '%d' with value '%s'",
				parser->current_token->e_type, parser->current_token->value);
		exit(1);
	}
	else
	{
		scmd->cmd_name = ft_strdup(parser->current_token->value);
		parser_get_next_token(parser);
		scmd->argc++;
		scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
					(scmd->argc - 1) * sizeof(*scmd->argv));
		scmd->argv[0] = ft_strdup(parser->current_token->value);
		while (parser->current_token->e_type == TOKEN_ID)
		{
			parser_get_next_token(parser);
			scmd->argc++;
			scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
						(scmd->argc - 1) * sizeof(*scmd->argv));
			scmd->argv[0] = ft_strdup(parser->current_token->value);
		}
		return (scmd);
	}
}
