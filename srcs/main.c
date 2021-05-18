/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/18 20:31:09 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/token_list.h"
#include "../libs/get_next_line/srcs/includes/get_next_line.h"
#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/token.h"
#include <stdio.h>
#include <sys/_types/_size_t.h>

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
		case TOKEN_PIPE: return ("TOKEN_PIPE");
		case TOKEN_DOLLAR: return ("TOKEN_DOLLAR");
		case BAD_TOKEN: return ("BAD_TOKEN");
		case TOKEN_EOF: return ("TOKEN_EOF");
		case TOKEN_CMD: return ("TOKEN_CMD");
		case TOKEN_FLAG: return ("TOKEN_FLAG");
		default: return ("Undefined token");
	}
}

void	print_ast(t_ast *ast)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ast->table_size)
	{
		printf("command='%s'\nargs:", ast->table_value[i]->cmd_name);
		printf("nodetype='%d'\n", ast->table_value[i]->e_nodetype);
		j = 0;
		while (j < ast->table_value[i]->argc)
		{
			printf("'%s'\t", ast->table_value[i]->argv[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_list_info(t_token_list **head)
{
	t_token_list	*save;

	save = *head;
	while (save)
	{
		printf("type = '%s'\t", print_token_type(save->token->e_type));
		printf("value = '%s'\n", save->token->value);
		save = save->next;
	}
}

int main(void)
{
	char			*str;
	t_lexer			*lexer;
	// t_token			*token;
	t_parser		*parser;
	t_ast			*root;

	get_next_line(0, &str);
	lexer = init_lexer(str);
	/* token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("type='%s'\tvalue='%s'\n", print_token_type(token->e_type), token->value);
		token = lexer_get_next_token(lexer);
	} */
	parser = init_parser(lexer);
	root = parser_parse_commands(parser);
	print_ast(root);
	printf("table_size = %zu\n", root->table_size);
	return (0);
}
