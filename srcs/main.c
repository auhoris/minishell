/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/10 21:05:00 by auhoris          ###   ########.fr       */
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

int main(void)
{
	char	*str = "echo 'hello ";
	t_lexer	*lexer;
	t_token	*token;

	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("TOKEN_TYPE = %d\t", token->e_type);
		printf("TOKEN_VALUE = %s\n", token->value);
		token = lexer_get_next_token(lexer);
	}
	return 0;
}
