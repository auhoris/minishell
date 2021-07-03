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

static char	*make_argument(char *str, t_parser *parser)
{
	char	*tmp;
	char	*itoa_tmp;

	tmp = str;
	if (parser->cur_tok->e_type == TOKEN_DOLLAR)
	{
		if (ft_strcmp(parser->cur_tok->value, "?") == 0)
		{
			itoa_tmp = ft_itoa(data_processing->ex_st);
			if (itoa_tmp == NULL)
				return (str);
			str = ft_strjoin(str, itoa_tmp);
			free(itoa_tmp);
		}
		else
			str = ft_strjoin(str,
					get_value_by_key(parser->cur_tok->value, &parser->env));
	}
	else
	{
		if (ft_strcmp(parser->cur_tok->value, "~") == 0)
			str = ft_strjoin(str, get_value_by_key("HOME", &parser->env));
		else
			str = ft_strjoin(str, parser->cur_tok->value);
	}
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
		if (type == ERROR_PARSER)
		{
			free(str);
			return (ft_strdup("error_parser"));
		}
	}
	str = make_argument(str, parser);
	if (str == NULL)
		return (NULL);
	if (parser_next_token(parser) == ERROR_PARSER)
	{
		free(str);
		return (ft_strdup("error_parser"));
	}
	return (str);
}

static int	parser_parse_redirect(t_parser *parser, t_ast *node)
{
	int	prev_type;
	int	curr_type;
	char	*file;

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
