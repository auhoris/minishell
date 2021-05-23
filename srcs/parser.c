#include "includes/parser.h"
#include "includes/lexer.h"
#include "includes/ast.h"
#include "includes/utils.h"
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
	static int	i;
	int			type;
	int			prev_type;

	parser->prev_token = parser->cur_tok;
	parser->cur_tok = lexer_get_next_token(parser->lexer);
	prev_type = parser->prev_token->e_type;
	type = parser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
		i = 0;
	/* printf("<=====>\n\n");
	printf("[Previous]:type='%d'|value='%s'\n", parser->prev_token->e_type, parser->prev_token->value);
	printf("[Current]:type='%d'|value='%s'\n", parser->cur_tok->e_type, parser->cur_tok->value);
	printf("\n\n<=====>\n\n"); */
	// printf("parser->cur_tok->number_of_tokens = %zu\n", parser->cur_tok->number_of_tokens);
	if (prev_type == BAD_TOKEN)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if (prev_type == TOKEN_PIPE && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if (type == TOKEN_SEMI && prev_type == TOKEN_SEMI)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if ((prev_type == TOKEN_SEMI || prev_type == TOKEN_PIPE) && i == 0)
	{
		printf("minishell: syntax error near unexpected token '%s'\n", parser->prev_token->value);
		exit(1);
	}
	else if ((prev_type == TOKEN_LESS
			|| prev_type == TOKEN_MORE
			|| prev_type == TOKEN_DMORE) && type == TOKEN_EOF)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		exit(1);
	}
	i++;
	destroy_token(parser->prev_token);
}

t_ast	*parser_parse_commands(t_parser *parser)
{
	t_ast	*cmd;
	t_ast	*scmd;

	cmd = init_node(NODE_ROOT);
	cmd->table_value = ft_calloc(1, sizeof(t_ast *));
	if (cmd->table_value == NULL)
		return (NULL);
	cmd->table_size++;
	cmd->table_value[cmd->table_size - 1] = parser_parse_command(parser);
	while (parser->cur_tok->e_type == TOKEN_SEMI)
	{
		parser_next_token(parser);
		scmd = parser_parse_command(parser);
		if (scmd)
		{
			cmd->table_size++;
			cmd->table_value = ft_realloc(cmd->table_value, cmd->table_size * sizeof(t_ast *), (cmd->table_size - 1) * sizeof(t_ast *));
			cmd->table_value[cmd->table_size - 1] = scmd;
		}

	}
	return (cmd);
}

t_ast	*parser_parse_command(t_parser *parser)
{
	t_ast	*command;

	command = init_node(NODE_SIMPLECOMMAND);
	if (command == NULL)
		return (NULL);
	while (parser->cur_tok->e_type != TOKEN_SEMI && parser->cur_tok->e_type != TOKEN_EOF)
	{
		if (parser->cur_tok->e_type == TOKEN_PIPE)
			return (parser_parse_pipe(command, parser));
		command = parser_parse_simple_command(parser);
	}
	return (command);
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

t_ast	*parser_parse_agruments(t_ast *scmd, t_parser *parser)
{
	scmd->argc++;
	scmd->argv = ft_realloc(scmd->argv, scmd->argc * sizeof(*scmd->argv),
						(scmd->argc - 1) * sizeof(*scmd->argv));
	if (scmd->argv == NULL)
		return (NULL);
	scmd->argv[scmd->argc - 1] = ft_strdup(parser->cur_tok->value);
	if (scmd->argv[scmd->argc - 1] == NULL)
		return (NULL);
	parser_next_token(parser);
	return (scmd);
}

char		*parser_get_dollar_value(t_token *token)
{
	(void)token;
	// Написать логику подстановки значения переменной окружения
	// Либо подставлять на этапе токенов?
	return (NULL);
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

char	*parser_get_cmd_name(t_parser *parser)
{
	char	*str;
	int		type;

	str = ft_strdup("");
	if (str == NULL)
		return (NULL);
	type = parser->cur_tok->e_type;
	while (!parser->cur_tok->f_space && parser->cur_tok->e_type != TOKEN_EOF)
	{
		if (type == TOKEN_DOLLAR || type == TOKEN_SEMI || type == TOKEN_MORE
			|| type == TOKEN_LESS || type == TOKEN_DMORE)
			return (str);
		str = connect_str(str, parser->cur_tok->value);
		if (str == NULL)
			return (NULL);
		parser_next_token(parser);
		type = parser->cur_tok->e_type;
	}
	// Зачем это?
	str = connect_str(str, parser->cur_tok->value);
	if (str == NULL)
		return (NULL);
	parser_next_token(parser);
	return (str);
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
		else if(parser->cur_tok->e_type == TOKEN_LESS)
			return (parser_parse_redirect(scmd, parser, NODE_LREDIRECT));
		else if (parser->cur_tok->e_type == TOKEN_DMORE)
			return (parser_parse_redirect(scmd, parser, NODE_DOUBLE_REDIRECT));
		if (parser_parse_agruments(scmd, parser) == NULL)
			return (NULL);
	}
	return (scmd);
}
