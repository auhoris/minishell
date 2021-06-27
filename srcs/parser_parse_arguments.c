#include "includes/env.h"
#include "includes/errors.h"
#include "includes/parser.h"
#include "includes/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

static char	*make_argument(char *str, t_parser *parser)
{
	int		type;
	char	*tmp;

	type = parser->cur_tok->e_type;
	// printf("%s\n", parser->cur_tok->value);
	tmp = str;
	if (type == TOKEN_DOLLAR)
	{
		if (ft_strcmp(parser->cur_tok->value, "?") == 0)
			str = ft_strjoin(str, "$?");
		else
		{
			str = ft_strjoin(str,
					get_value_by_key(parser->cur_tok->value, &parser->env));
		}
	}
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
		if (str == NULL)
			return (NULL);
		type = parser_next_token(parser);
		if (type == ERROR)
		{
			free(str);
			return (ft_strdup("error_parser"));
		}
	}
	str = make_argument(str, parser);
	if (str == NULL || parser_next_token(parser) == ERROR)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static int	parser_parse_redirect(t_parser *parser, t_ast *node)
{
	int	prev_type;
	int	curr_type;

	prev_type = parser->cur_tok->e_type;
	while (prev_type == TOKEN_MORE
		|| prev_type == TOKEN_LESS
		|| prev_type == TOKEN_DMORE)
	{
		curr_type = parser_next_token(parser);
		if (curr_type == TOKEN_PIPE || curr_type == TOKEN_SEMI)
			return (ERROR_PARSER);
		if (curr_type == ERROR_PARSER || curr_type == TOKEN_DOLLAR)
			return (ERROR_PARSER);
		if (make_node_fd(parser->cur_tok->value, prev_type, node) != OK)
			return (ERROR_PARSER);
		prev_type = parser_next_token(parser);
		if (prev_type == ERROR_PARSER)
			return (ERROR_PARSER);
		check_fd(node, prev_type);
	}
	if (parser->cur_tok->e_type == TOKEN_ID)
	{
		node->cmd_name = ft_strdup(parser->cur_tok->value);
		if (parser_next_token(parser) == ERROR_PARSER)
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
		if (ft_strcmp(node->argv[node->argc - 1], "error_parser") == 0)
			return (ast_error_handler(node, ERROR_PARSER));
		if (node->argv[node->argc - 1] == NULL)
			return (ast_error_handler(node, ERROR_MALLOC));
	}
	return (node);
}
