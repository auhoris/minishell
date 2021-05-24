/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/24 21:28:12 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/lexer.h"
#include "includes/minishell.h"

#include "includes/token_list.h"
#include "../libs/get_next_line/srcs/includes/get_next_line.h"
#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/token.h"
#include <stdio.h>
#include "includes/visitor.h"
#include <sys/_types/_size_t.h>
#include "includes/env.h"

// char	*print_token_type(int type)
// {
// 	switch (type) {
// 		case TOKEN_ID: return ("TOKEN_ID");
// 		case TOKEN_BSLASH: return ("TOKEN_BSLASH");
// 		case TOKEN_SQUOTE: return ("TOKEN_SQUOTE");
// 		case TOKEN_DQUOTE: return ("TOKEN_DQUOTE");
// 		case TOKEN_SEMI: return ("TOKEN_SEMI");
// 		case TOKEN_LESS: return ("TOKEN_LESS");
// 		case TOKEN_MORE: return ("TOKEN_MORE");
// 		case TOKEN_DMORE: return ("TOKEN_DMORE");
// 		case TOKEN_EQUALS: return ("TOKEN_EQUALS");
// 		case TOKEN_PIPE: return ("TOKEN_PIPE");
// 		case TOKEN_DOLLAR: return ("TOKEN_DOLLAR");
// 		case BAD_TOKEN: return ("BAD_TOKEN");
// 		case TOKEN_EOF: return ("TOKEN_EOF");
// 		case TOKEN_CMD: return ("TOKEN_CMD");
// 		// case TOKEN_FLAG: return ("TOKEN_FLAG");
// 		default: return ("Undefined token");
// 	}
// }

int	main(int argc, char **argv, char **env)
{
	t_env_dict	**env_dict;

	(void)argc;
	(void)argv;
	env_dict = init_env(env);
	// printf("hi\n");
	// check_input_params(argc, argv);
	termcap(env_dict);
	return (0);
}
