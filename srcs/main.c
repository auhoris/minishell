/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlados_paperos <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:34:19 by vlados_pa         #+#    #+#             */
/*   Updated: 2021/05/11 16:45:58 by auhoris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/lexer.h"
#include "includes/minishell.h"


int main(int argc, char **argv)
{
	check_input_params(argc, argv);
	termcap();
	return 0;
}
