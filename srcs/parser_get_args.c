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

static char	*handle_dollar_token(char *str)
{
	char	*itoa_tmp;

	itoa_tmp = ft_itoa(g_data_processing->ex_st);
	if (itoa_tmp == NULL)
		return (NULL);
	str = ft_strjoin(str, itoa_tmp);
	free(itoa_tmp);
	return (str);
}

/* itoa_tmp = ft_itoa(g_data_processing->ex_st);
if (itoa_tmp == NULL)
	return (str);
str = ft_strjoin(str, itoa_tmp);
free(itoa_tmp); */

		/* if (handle_dollar_token(parser, str) == ERROR_MALLOC)
			return (str); */
static char	*make_argument(char *str, t_parser *parser)
{
	char	*tmp;

	tmp = str;
	if (parser->cur_tok->e_type == TOKEN_DOLLAR)
	{
		if (ft_strcmp(parser->cur_tok->value, "?") == 0)
			str = handle_dollar_token(str);
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

static char	*handle_get_args(char *str, t_parser *parser, int *type)
{
	str = make_argument(str, parser);
	if (str == NULL)
		return (NULL);
	*type = parser_next_token(parser);
	if (*type == ERROR_PARSER)
	{
		free(str);
		return (ft_strdup("error_parser"));
	}
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
		str = handle_get_args(str, parser, &type);
		if (str == NULL || ft_strcmp(str, "error_parser") == 0)
			return (str);
	}
	str = handle_get_args(str, parser, &type);
	return (str);
}

/* str = make_argument(str, parser);
if (str == NULL)
	return (NULL);
type = parser_next_token(parser);
if (type == ERROR_PARSER)
{
	free(str);
	return (ft_strdup("error_parser"));
} */
/* str = make_argument(str, parser);
if (str == NULL)
	return (NULL);
if (parser_next_token(parser) == ERROR_PARSER)
{
	free(str);
	return (ft_strdup("error_parser"));
} */
