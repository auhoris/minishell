/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/31 16:55:58 by auhoris          ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_env_list	*env_dict;

	(void)argc;
	(void)argv;
	env_dict = init_env_list(env);
	// show_dict(&env_dict);
	// printf("hi\n");
	// check_input_params(argc, argv);
	termcap(env_dict);
	return (0);
}
