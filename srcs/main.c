/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/07/03 15:34:56 by vlados_pa        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lexer.h"
#include "includes/minishell.h"
#include "includes/exit_status.h"
#include "includes/token_list.h"
#include "includes/parser.h"
#include "includes/ast.h"
#include "includes/token.h"
#include "includes/types.h"
#include "./history/history.h"
#include <stdio.h>
#include "includes/visitor.h"
#include "includes/env.h"
#include <sys/_types/_size_t.h>
#include <term.h>

/* g_data_processing->ex_st = 1;
get_last_element(&g_data_processing->actual_history); */
void	handler(int s)
{
	(void)s;
	if (g_data_processing != NULL)
	{
		free(g_data_processing->command_line);
		g_data_processing->command_line = ft_calloc(1, 1);
	}
	g_data_processing->ex_st = 1;
	g_data_processing->num_symbol = 0;
	get_last_element(&g_data_processing->actual_history);
	ft_putstr("\n<minishell>$ ");
	tputs(tgetstr("sc", 0), 1, ft_putint);
}

void	test(void)
{
	printf("\ntest\n");
}

int	main(int argc, char **argv, char **env)
{
	t_env_list	*env_dict;

	(void)argc;
	(void)argv;
	g_data_processing = NULL;
	env_dict = init_env_list(env);
	termcap(env_dict);
	return (0);
}
