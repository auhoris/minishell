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

#include "term.h"
#include "includes/lexer.h"

int main(int argc, char **argv)
{
	char	str[2000];
	int		l;
	struct termios term;

	argc = 0;
	argv = NULL;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;

	l = read(1, str, 100);

	write(1, str, l);
	write(1, "\n", 1);

	return 0;
}
