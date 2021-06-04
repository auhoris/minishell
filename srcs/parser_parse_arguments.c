#include "includes/parser.h"
#include "includes/token.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

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
	str = make_argument(str, parser);
	if (str == NULL || parser_next_token(parser) == ERROR)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

static int	create_file(char *filename, int type, t_ast *node)
{
	if (type == TOKEN_MORE || type == TOKEN_DMORE)
	{
		if (type == TOKEN_MORE)
			node->fd_out = open(filename, O_CREAT | O_WRONLY | O_EXCL);
		else
			node->fd_out = open(filename, O_CREAT | O_WRONLY | O_APPEND);
		node->out_file = ft_strdup(filename);
		if (node->out_file == NULL)
			return (ERROR);
	}
	else
	{
		node->fd_in = open(filename, O_CREAT | O_RDONLY | O_EXCL);
		node->in_file = ft_strdup(filename);
		if (node->in_file == NULL)
			return (ERROR);
	}
	if (node->fd_out == -1 || node->fd_in == -1)
		return (ERROR);
	return (OK);
}

static int	parser_parse_redirect(t_parser *parser, t_ast *node)
{
	int	prev_type;
	int	curr_type;

	prev_type = parser->cur_tok->e_type;
	while (prev_type == TOKEN_MORE
		|| prev_type == TOKEN_LESS || prev_type == TOKEN_DMORE)
	{
		if (prev_type == TOKEN_DMORE
			|| prev_type == TOKEN_LESS || prev_type == TOKEN_MORE)
		{
			if (node->fd_out != STDOUT_FILENO)
				close(node->fd_out);
			free(node->out_file);
			free(node->in_file);
			if (node->fd_in != STDIN_FILENO)
				close(node->fd_in);
		}
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
