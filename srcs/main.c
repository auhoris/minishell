/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/11 15:07:19 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
		case TOKEN_DQUOTE: return ("TOKEN_DQUOTE");//3
		case TOKEN_SEMICOLON: return ("TOKEN_SEMICOLON");//4
		case TOKEN_LESS: return ("TOKEN_LESS");//5
		case TOKEN_MORE: return ("TOKEN_MORE");//6
		case TOKEN_DMORE: return ("TOKEN_DMORE");//7
		case TOKEN_PIPE: return ("TOKEN_PIPE");//8
		case TOKEN_DOLLAR: return ("TOKEN_ID");//9
		case TOKEN_NULL: return ("TOKEN_ID");//10
		case TOKEN_EOF: return ("TOKEN_ID");//11
		default: return ("Undefined token");
	}
}

int main(void)
{
	char	*str = "echo >> hello 'string' cd < > ; |";
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("type = '%s'\t", print_token_type(token->e_type));
		printf("value = '%s'\n", token->value);
		token = lexer_get_next_token(lexer);
	}
	return 0;
}
