/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/06/29 22:42:51 by vlados_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/exit_status.h"
#include "includes/token_list.h"
#include "../libs/get_next_line/srcs/includes/get_next_line.h"
#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/token.h"
#include "includes/types.h"
#include <stdio.h>
#include "includes/visitor.h"
#include "includes/env.h"
#include <sys/_types/_size_t.h>
#include <term.h>

void	handler(int s)
{
	(void)s;
	if (data_processing != NULL)
	{
		// printf("\ncmdline = %s\n", data_processing->command_line);
		free(data_processing->command_line);
		data_processing->command_line = ft_calloc(1,1);

	}
	ft_putstr("\n<minishell>$ ");
	tputs(tgetstr("sc", 0), 1, ft_putint);

}

void	test()
{
	printf("\ntest\n");
}

int	main(int argc, char **argv, char **env)
{
	t_env_list	*env_dict;

	(void)argc;
	(void)argv;
	// data_processing->ex_st = OK;
	data_processing = NULL;
	env_dict = init_env_list(env);
	termcap(env_dict);
	return (0);
}
