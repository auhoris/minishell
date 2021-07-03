#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/wait.h>
#include <term.h>
#include <unistd.h>
#include "termcap.h"
#include "../includes/minishell.h"
#include "../includes/types.h"
#include "../includes/env.h"
#include "../executor/executor.h"
#include "../includes/exit_status.h"

static int	processing_del(char **command_line, int *num_symbol)
{
	char	*temp;
	int		len;

	len = ft_strlen(*command_line);
	if (len != 0)
	{
		temp = *command_line;
		*command_line = ft_substr(temp, 0, len - 1);
		if (*command_line == NULL)
			return (ERROR_MALLOC);
		free(temp);
	}
	if (*num_symbol > 0)
	{
		tputs(tgetstr("le", 0), 1, ft_putint);
		tputs(tgetstr("dc", 0), 1, ft_putint);
		(*num_symbol)--;
	}
	return (OUT);
}

static int	processing_button(t_data_processing *g_data_processing, int button)
{
	int	out;

	if (g_data_processing->actual_history == NULL && button != ENTER)
		return (OUT);
	screen_clear();
	out = get_history_data(g_data_processing, button);
	if (out != OUT)
		return (out);
	if (button == ENTER)
	{
		out = write_enter(g_data_processing);
		if (out != OUT && out != ERROR_BAD_COMMAND && out != ERROR_PARSER)
			return (out);
		tputs(tgetstr("sc", 0), 1, ft_putint);
		free(g_data_processing->command_line);
		g_data_processing->command_line = (char *)ft_calloc(1, 1);
		if (g_data_processing->command_line == NULL)
			return (ERROR_MALLOC);
		g_data_processing->num_symbol = 0;
	}
	else
		write_in_terminal(g_data_processing->command_line,
			&g_data_processing->num_symbol);
	return (out);
}

static int	input_processing(t_data_processing *g_data_processing)
{
	int	check_buf;
	int	out;

	check_buf = check_buf_read(g_data_processing->buf_read);
	out = OUT;
	if (check_buf == UP)
		out = processing_button(g_data_processing, UP);
	else if (check_buf == DOWN)
		out = processing_button(g_data_processing, DOWN);
	else if (check_buf == DEL)
		out = processing_del(&g_data_processing->command_line,
				&g_data_processing->num_symbol);
	else if (check_buf == ENTER)
		out = processing_button(g_data_processing, ENTER);
	else if (check_buf == ISPRINT)
		out = write_in_terminal_isprint(g_data_processing);
	else if (check_buf == CTRL_D)
		ctrl_d(g_data_processing);
	return (out);
}

static int	infinite_round(t_env_list *env, struct termios *term,
				struct termios *term_default)
{
	int		l;
	int		out;

	out = OUT;
	g_data_processing = init_data_processing(env);
	if (g_data_processing == NULL)
		return (ERROR_MALLOC);
	g_data_processing->term = term;
	g_data_processing->term_default = term_default;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler);
		g_data_processing->term->c_lflag &= ~(ECHO);
		g_data_processing->term->c_lflag &= ~(ICANON);
		tcsetattr(0, TCSANOW, g_data_processing->term);
		l = read(0, g_data_processing->buf_read, BUFFER_SIZE);
		if (l != 0)
		{
			out = input_processing(g_data_processing);
			error_processing(env, g_data_processing, out);
		}
		ft_bzero(g_data_processing->buf_read, BUFFER_SIZE);
	}
}

int	termcap(t_env_list *env)
{
	struct termios	term;
	struct termios	term_default;

	if (get_term_param(&term, &term_default) != OUT)
		return (ERROR);
	write(1, "<minishell>$ ", 13);
	tputs(tgetstr("sc", 0), 1, ft_putint);
	infinite_round(env, &term, &term_default);
	return (1);
}
