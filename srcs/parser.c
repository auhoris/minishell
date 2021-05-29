#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/utils.h"
#include "includes/visitor.h"
#include <stdlib.h>

t_parser	*init_parser(t_lexer *lexer, t_env_list *env)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->lexer = lexer;
	parser->prev_token = NULL;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	if (parser->cur_tok == NULL)
	{
		free(parser);
		return (NULL);
	}
	parser->env = env;
	return (parser);
}

t_ast	*parser_parse_commands(t_parser *parser)
{
	t_ast	*cmd;
	t_ast	*scmd;

	cmd = init_node(NODE_ROOT);
	if (cmd == NULL)
		return (NULL);
	cmd->table_value = ft_calloc(1, sizeof(t_ast *));
	if (cmd->table_value == NULL)
		return (cmd);
	cmd->table_size++;
	cmd->table_value[cmd->table_size - 1] = parser_parse_command(parser);
	if (cmd->table_value[cmd->table_size - 1] == NULL)
		return (cmd);
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		if (parser_next_token(parser) == ERROR)
			return (cmd);
		scmd = parser_parse_command(parser);
		if (scmd)
		{
			cmd->table_size++;
			cmd->table_value = ft_realloc(cmd->table_value,
					cmd->table_size * sizeof(t_ast *),
					(cmd->table_size - 1) * sizeof(t_ast *));
			cmd->table_value[cmd->table_size - 1] = scmd;
		}
		else
			break ;
	}
	return (cmd);
}

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*command;

	command = NULL;
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF)
	{
		if (parser->cur_tok->e_type == TOKEN_PIPE)
			return (parser_parse_pipe(command, parser));
		command = parser_parse_simple_command(parser);
		if (command == NULL)
			return (command);
	}
	return (command);
}

t_ast	*parser_parse_pipe(t_ast *left_node, t_parser *parser)
{
	t_ast	*pipe_node;

	pipe_node = init_node(NODE_PIPE);
	pipe_node->table_value = ft_calloc(2, sizeof(t_ast *));
	pipe_node->table_value[0] = left_node;
	if (parser_next_token(parser) == ERROR)
		return (pipe_node);
	pipe_node->table_value[1] = parser_parse_command(parser);
	return (pipe_node);
}

t_ast	*parser_parse_redirect(t_ast *left_node, t_parser *parser, int type)
{
	t_ast	*redirect;

	redirect = init_node(type);
	redirect->table_value = ft_calloc(2, sizeof(t_ast *));
	redirect->table_value[0] = left_node;
	if (parser_next_token(parser) == ERROR)
		return (redirect);
	redirect->table_value[1] = parser_parse_simple_command(parser);
	return (redirect);
}

static char	*make_argument(char *str, t_parser *parser)
{
	int		type;
	char	*tmp;

	type = parser->cur_tok->e_type;
	tmp = str;
	if (type == TOKEN_DOLLAR)
		str = ft_strjoin(str, get_value_by_key(parser->cur_tok, &parser->env));
	else
		str = ft_strjoin(str, parser->cur_tok->value);
	free(tmp);
	if (str == NULL)
		return (NULL);
	return (str);
}

char	*parser_get_cmd_name(t_parser *parser)
{
	char	*str;
	int		type;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	type = parser->cur_tok->e_type;
	while (!parser->cur_tok->f_space && type != TOKEN_EOF)
	{
		if (type == TOKEN_SEMI || type == TOKEN_MORE
			|| type == TOKEN_LESS || type == TOKEN_DMORE
			|| type == TOKEN_PIPE || type == ERROR)
			return (str);
		str = make_argument(str, parser);
		if (str == NULL)
			return (NULL);
		type = parser_next_token(parser);
	}
	// Зачем это? - Это нада
	str = make_argument(str, parser);
	if (str == NULL)
		return (NULL);
	parser_next_token(parser);
	return (str);
}

t_ast	*parser_parse_agruments(t_ast *scmd, t_parser *parser)
{
	scmd->argc++;
	scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
			(scmd->argc - 1) * sizeof(*scmd->argv));
	if (scmd->argv == NULL)
		return (NULL);
	scmd->argv[scmd->argc - 1] = parser_get_cmd_name(parser);
	return (scmd);
}

t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*scmd;

	scmd = init_node(NODE_SIMPLECOMMAND);
	if (scmd == NULL)
		return (NULL);
	scmd->cmd_name = parser_get_cmd_name(parser);
	if (scmd->cmd_name == NULL)
		return (NULL);
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF
		&& parser->cur_tok->e_type != TOKEN_PIPE)
	{
		if (parser->cur_tok->e_type == TOKEN_MORE)
			return (parser_parse_redirect(scmd, parser, NODE_RREDIRECT));
		else if (parser->cur_tok->e_type == TOKEN_LESS)
			return (parser_parse_redirect(scmd, parser, NODE_LREDIRECT));
		else if (parser->cur_tok->e_type == TOKEN_DMORE)
			return (parser_parse_redirect(scmd, parser, NODE_DOUBLE_REDIRECT));
		if (parser_parse_agruments(scmd, parser) == NULL)
			return (NULL);
	}
	return (scmd);
}

//Пока бесполезняк
/* t_ast	*parser_parse_variable_definition(t_parser *parser)
{
	t_ast	*vardef;

	vardef = init_node(NODE_VARDEF);
	if (vardef == NULL)
		return (NULL);
	printf("prev %s\n", parser->prev_token->value);
	printf("curr %s\n", parser->cur_tok->value);
	vardef->var_name = ft_strdup(parser->prev_token->value);
	if (vardef->var_name == NULL)
		return (NULL);
	printf("%s\n", vardef->var_name);
	printf("%s\n", vardef->var_value);
	parser_next_token(parser);
	vardef->var_value = ft_strdup(parser->cur_tok->value);
	if (vardef->var_value == NULL)
		return (NULL);
	return (vardef);
} */
