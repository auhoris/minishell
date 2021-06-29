#include <stdlib.h>
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

static int	get_term_param(struct termios *term, struct termios *term_default)
{
	char	*term_name;
	int		out;

	term_name = getenv("TERM");
	if (term_name == NULL)
		return (ERROR_TERM_NAME);
/*
	tcgetattr заполнит структуру term в соответствии с параметрами нашего терминала
*/
	out = tcgetattr(0, term);
	tcgetattr(0, term_default);
	if (out != 0)
	{
		// ERROR (есть errno)
	}
/*
	~(ECHO) не отображать вводимые символы
	~(ICANON) выкл канонический режим (теперь мы видим то, что вводим)
	tcsetattr(0, TCSANOW, term) - If optional_actions is TCSANOW, the change shall occur immediately (изменения произойдут немедленно).
*/
	// printf("\n%lu\n", term->c_lflag);
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, term);
/*
	tgetent
	Вернет строку с описанием используемого терминала
	Первый аргумент 0, чтобы ф-я сама выделила память
	Он возвращает 1 в случае успеха, 0, если такой записи нет, и -1, если база данных terminfo не может быть найдена.
*/
	out = tgetent(0, term_name);
	if (out == 0)
	{
		// ERROR
	}
	else if (out == -1)
	{
		// ERROR
	}
	return (OUT);
}

void		screen_clear(void)
{
/*
	rc восстановление сохраненной позиции курсора
	cd очистка до конца экрана
*/
	tputs(tgetstr("rc", 0), 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
}

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
/*
	le смещение каретки на 1 влево
	dc удаление символа
*/
		tputs(tgetstr("le", 0), 1, ft_putint);
		tputs(tgetstr("dc", 0), 1, ft_putint);
		(*num_symbol)--;
	}
	return (OUT);
}

// Пофиксить случай при постоянном нажатии ENTER
static int	processing_button(t_data_processing *data_processing, int button)
{
	int	out;

	if (data_processing->actual_history == NULL && button != ENTER)
		return (OUT);
	screen_clear();
	out = get_history_data(data_processing, button);
	if (out != OUT)
		return (out);
	if (button == ENTER)
	{
		if (*data_processing->command_line == '\0')
			data_processing->n_flag = FALSE;
		data_processing->permission_create = 1;
		if (*data_processing->command_line != '\0')
		{
			write(1, data_processing->command_line, ft_strlen(data_processing->command_line));
			out = start_parsing(data_processing);
			if (out != OUT && out != ERROR_BAD_COMMAND && out != ERROR_PARSER)
			{
				printf("ERROR = %d\n", out);
				return (out);
			}
		}
		if (data_processing->n_flag == FALSE)
			ft_putstr("\n<minishell>$[1] ");
		else if (data_processing->n_flag == TRUE)
			ft_putstr("<minishell>$[2] ");
		data_processing->size_pids = 0;
		tputs(tgetstr("sc", 0), 1, ft_putint);
		free(data_processing->command_line);
		data_processing->command_line = (char *)ft_calloc(1, 1);
		if (data_processing->command_line == NULL)
			return (ERROR_MALLOC);
		data_processing->num_symbol = 0;
	}
	else
		write_in_terminal(data_processing->command_line, &data_processing->num_symbol);
	return (out);
}

static int	input_processing(t_data_processing *data_processing)
{
	int	check_buf;
	int	out;

	check_buf = check_buf_read(data_processing->buf_read);
	out = OUT;
	if (check_buf == UP)
	{
		out = processing_button(data_processing, UP);
	}
	else if (check_buf == DOWN)
	{
		out = processing_button(data_processing, DOWN);
	}
	else if (check_buf == DEL)
	{
		out = processing_del(&data_processing->command_line, &data_processing->num_symbol);
	}
	else if (check_buf == ENTER)
	{
		out = processing_button(data_processing, ENTER);
		// printf("\nпосле processing_button |%d|\n", out);
	}
	else if (check_buf == ISPRINT)
	{
		out = write_in_terminal_isprint(data_processing);
	}
	else if (check_buf == CTRL_D)
		ctrl_d(data_processing);
	return (out);
}

static int		infinite_round(t_env_list *env, struct termios *term, struct termios *term_default)
{
	int		l;
	int		out;

	out = OUT;
	data_processing = init_data_processing(env);
	if (data_processing == NULL)
		return (ERROR_MALLOC);
	data_processing->term = term;
	data_processing->term_default = term_default;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler);
		data_processing->term->c_lflag &= ~(ECHO);
		data_processing->term->c_lflag &= ~(ICANON);
		tcsetattr(0, TCSANOW, data_processing->term);
		l = read(0, data_processing->buf_read, BUFFER_SIZE);
		if (l != 0)
		{
			out = input_processing(data_processing);
			error_processing(env, data_processing, out);
		}
		ft_bzero(data_processing->buf_read, BUFFER_SIZE);
	}
}

int		termcap(t_env_list *env)
{
	struct termios	term;
	struct termios	term_default;

	if (get_term_param(&term, &term_default) != 1)
	{
		// ERROR
	}
	write(1, "<minishell>$ ", 13);
/*
	sc сохранение позиции каретки
*/
	tputs(tgetstr("sc", 0), 1, ft_putint);
	infinite_round(env, &term, &term_default);
	return (1);
}
