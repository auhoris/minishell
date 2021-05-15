/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/15 17:31:40 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/token_list.h"
#include "../libs/get_next_line/srcs/includes/get_next_line.h"

void	lexer_print_data(t_lexer *lexer)
{
	printf("%s\n", lexer->content);
	printf("%c\n", lexer->c);
	printf("%zu\n", lexer->current);
	printf("lexer->length = %zu\n", lexer->length);
}

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
	t_token			*token;
	t_token_list	*head;

	get_next_line(0, &str);
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		list_push_back(&head, list_new_token(token));
		token = lexer_get_next_token(lexer);
	}
	print_list_info(&head);
	
	return (0);
}
