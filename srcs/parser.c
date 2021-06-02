#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/env.h"
#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

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

t_ast	*ast_error_handler(t_ast *node)
{
	node->err_handler = ERROR;
	return (node);
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
		if (simple_node)
		{
			node->table_size++;
			node->table_value = ft_realloc(node->table_value,
					node->table_size * sizeof(t_ast *),
					(node->table_size - 1) * sizeof(t_ast *));
			if (node->table_value == NULL)
				return (ast_error_handler(node));
			node->table_value[node->table_size - 1] = simple_node;
		}
		else
			return (ast_error_handler(node));
	}
	return (node);
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

char	*parser_get_args(t_parser *parser)
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
		type = parser_next_token(parser);
		if (str == NULL || type == ERROR)
		{
			free(str);
			return (NULL);
		}
	}
	// Зачем это? - Это нада
	str = make_argument(str, parser);
	if (str == NULL || parser_next_token(parser) == ERROR)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

int	create_file(char *filename, int type, t_ast *node)
{
	int		fd;

	if (type == TOKEN_MORE || type == TOKEN_DMORE)
	{
		if (type == TOKEN_MORE)
			fd = open(filename, O_CREAT | O_WRONLY);
		else
			fd = open(filename, O_CREAT | O_WRONLY | O_APPEND);
		node->out_file = ft_strdup(filename);
		if (node->out_file == NULL)
			return (ERROR);
	}
	else
	{
		fd = open(filename, O_CREAT | O_RDONLY | O_TRUNC);
		node->in_file = ft_strdup(filename);
		if (node->in_file == NULL)
			return (ERROR);
	}
	if (fd == -1)
		return (ERROR);
	close(fd);
	return (OK);
}

int	parser_parse_redirect(t_parser *parser, t_ast *node)
{
	int	prev_type;
	int	curr_type;

	prev_type = parser->cur_tok->e_type;
	while (prev_type == TOKEN_MORE || prev_type == TOKEN_LESS || prev_type == TOKEN_DMORE)
	{
		curr_type = parser_next_token(parser);
		if (curr_type == ERROR || curr_type == TOKEN_DOLLAR)
			return (ERROR);
		if (create_file(parser->cur_tok->value, prev_type, node) == ERROR)
			return (ERROR);
		prev_type = parser_next_token(parser);
		if (prev_type == ERROR)
			return (ERROR);
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
		if (node->err_handler == ERROR)
			return (ast_error_handler(node));
	}
	else
	{
		node->argc++;
		node->argv = ft_realloc(node->argv, node->argc * sizeof(*node->argv),
				(node->argc - 1) * sizeof(*node->argv));
		if (node->argv == NULL)
			return (ast_error_handler(node));
		node->argv[node->argc - 1] = parser_get_args(parser);
		if (node->argv[node->argc - 1] == NULL)
			return (ast_error_handler(node));
	}
	return (node);
}

t_ast	*parser_parse_simple_command(t_parser *parser)
{
	t_ast	*node;

	node = init_node(NODE_SIMPLECOMMAND);
	if (node == NULL)
		return (NULL);
	node->cmd_name = parser_get_args(parser);
	if (node->cmd_name == NULL)
		return (NULL);
	while (parser->cur_tok->e_type != TOKEN_SEMI
		&& parser->cur_tok->e_type != TOKEN_EOF
		&& parser->cur_tok->e_type != TOKEN_PIPE)
	{
		parser_parse_agruments(node, parser);
		if (node->err_handler == ERROR)
			return (node);
	}
	return (node);
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
