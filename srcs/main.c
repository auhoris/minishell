/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/19 17:17:16 by auhoris          ###   ########.fr       */
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

char	*print_node_type(int type)
{
	switch (type) {
		case NODE_ROOT: return ("NODE_ROOT");
		case NODE_PIPE: return ("NODE_PIPE");
		case NODE_LREDIRECT: return ("NODE_LREDIRECT");
		case NODE_RREDIRECT: return ("NODE_RREDIRECT");
		case NODE_DOUBLE_REDIRECT: return ("NODE_DOUBLE_REDIRECT");
		case NODE_SEQUENCE: return ("NODE_SEQUENCE");
		case NODE_SIMPLECOMMAND: return ("NODE_SIMPLECOMMAND");
		default: return ("Undefined token");
	}
}

void	visit_root(t_ast *node);
void	print_nodes(t_ast *node);

void	visit_simplecommand(t_ast *node)
{
	size_t	i;

	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	printf("command name = %s\t", node->cmd_name);
	i = 0;
	while (i < node->argc)
	{
		printf("argv[%zu] = %s\t", i, node->argv[i]);
		i++;
	}
	printf("\n\n<========>\n\n");
}

void	visit_pipe(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	print_nodes(node->table_value[0]);
	print_nodes(node->table_value[1]);
}

void	visit_redirect(t_ast *node)
{
	printf("nodetype='%s'\n", print_node_type(node->e_nodetype));
	print_nodes(node->table_value[0]);
	print_nodes(node->table_value[1]);
}

void	print_nodes(t_ast *node)
{
	if (node->e_nodetype == NODE_ROOT)
		visit_root(node);
	if (node->e_nodetype == NODE_SIMPLECOMMAND)
		visit_simplecommand(node);
	if (node->e_nodetype == NODE_PIPE)
		visit_pipe(node);
	if (node->e_nodetype == NODE_LREDIRECT || node->e_nodetype == NODE_RREDIRECT || node->e_nodetype == NODE_DOUBLE_REDIRECT)
		visit_redirect(node);
}

void	visit_root(t_ast *node)
{
	size_t	i;

	i = 0;
	while (i < node->table_size)
	{
		print_nodes(node->table_value[i]);
		i++;
	}
}

int main(void)
{
	char			*str;
	t_lexer			*lexer;
	// t_token			*token;
	t_parser		*parser;
	t_ast			*root;

	// printf("[minishell]: ");
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
	print_nodes(root);
	// printf("table_size = %zu\n", root->table_size);
	return (0);
}
