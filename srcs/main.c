/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/24 15:56:19 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/token_list.h"
#include "../libs/get_next_line/srcs/includes/get_next_line.h"
#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/token.h"
#include <stdio.h>
#include "includes/visitor.h"
#include <sys/_types/_size_t.h>
#include "includes/env.h"

char	*print_token_type(int type)
{
	switch (type) {
		case TOKEN_ID: return ("TOKEN_ID");
		case TOKEN_BSLASH: return ("TOKEN_BSLASH");
		case TOKEN_SQUOTE: return ("TOKEN_SQUOTE");
		case TOKEN_DQUOTE: return ("TOKEN_DQUOTE");
		case TOKEN_SEMI: return ("TOKEN_SEMI");
		case TOKEN_LESS: return ("TOKEN_LESS");
		case TOKEN_MORE: return ("TOKEN_MORE");
		case TOKEN_DMORE: return ("TOKEN_DMORE");
		case TOKEN_EQUALS: return ("TOKEN_EQUALS");
		case TOKEN_PIPE: return ("TOKEN_PIPE");
		case TOKEN_DOLLAR: return ("TOKEN_DOLLAR");
		case BAD_TOKEN: return ("BAD_TOKEN");
		case TOKEN_EOF: return ("TOKEN_EOF");
		case TOKEN_CMD: return ("TOKEN_CMD");
		// case TOKEN_FLAG: return ("TOKEN_FLAG");
		default: return ("Undefined token");
	}
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	// printf("!!!ENV!!!\n");
	while (env[++i])
	{
		printf("%c\n", env[i][0]);
		// printf("%s\n", env[i]);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char		*str;
	t_lexer		*lexer;
	/* t_parser	*parser;
	t_ast		*root; */
	t_token		*token;
	// t_env_dict	**env_d;


	get_next_line(0, &str);
	lexer = init_lexer(str);
	/* while (get_next_line(0, &str) > 0)
	{ */
		/* lexer = init_lexer(str);
		parser = init_parser(lexer, init_env(env));
		root = parser_parse_commands(parser); */
	// }
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("type='%s'\tvalue='%s'\tspace_flag='%d'\n", print_token_type(token->e_type), token->value, token->f_space);
		token = lexer_get_next_token(lexer);
	}
	// visitor_visit_nodes(root);
	// printf("table_size = %zu\n", root->table_size);
	return (0);
}
