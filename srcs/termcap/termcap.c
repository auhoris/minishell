#include "../includes/types.h"
#include <term.h>
#include "../includes/lexer.h"
#include "termcap.h"

static int		get_term_param(struct termios *term)
{
	char	*term_name;
	int		out;

	term_name = getenv("TERM");
	if (term_name == NULL)
	{
		// ERROR
	}


	out = tcgetattr(0, term); // заполнит структуру term в соответствии с параметрами нашего терминала
	if (out != 0)
	{
		// ERROR (есть errno)
	}
	term->c_lflag &= ~(ECHO); // не отображать вводимые символы
	term->c_lflag &= ~(ICANON); // выкл канонический режим (теперь мы видим то, что вводим)
	tcsetattr(0, TCSANOW, term); // If optional_actions is TCSANOW, the change shall occur immediately (изменения произойдут немедленно).

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
	return (1);
}

void		screen_clear(void)
{
	tputs(tgetstr("rc", 0), 1, ft_putint); // rc восстановление сохраненной позиции курсора
	tputs(tgetstr("cd", 0), 1, ft_putint); // очистка до конца экрана
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
		tputs(tgetstr("le", 0), 1, ft_putint); // смещение каретки на 1 влево
		tputs(tgetstr("dc", 0), 1, ft_putint); // удаление символа
		(*num_symbol)--;
	}
	return (1);
}

static int	processing_button(t_data_processing *data_processing, int button)
{
	int	out;

	if (data_processing->actual_history == NULL && button != ENTER)
		return (OUT);
	screen_clear();
	// out = get_history_list(data_processing, button);
	out = get_history_data(data_processing, button);
	if (button == ENTER)
	{
		data_processing->permission_create = 1;
		if (*data_processing->command_line != '\0')
		{
			write(1, " выполнение команды ", 38);
			write(1, data_processing->actual_history->prev->command, ft_strlen(data_processing->actual_history->prev->command));
		}
		write(1, "\n<minishell>$", 13);
		tputs(tgetstr("sc", 0), 1, ft_putint);										// сохранили позицию каретки
		free(data_processing->command_line);
		data_processing->command_line = (char *)ft_calloc(1, 1);					// нет защиты
		data_processing->num_symbol = 0;
	}
	else
		write_in_terminal(data_processing->command_line, &data_processing->num_symbol);
	return (out);
}

static int	input_processing(t_data_processing *data_processing)
{
	int		check_buf;
	int	out;

	check_buf = check_buf_read(data_processing->buf_read);
	out = OUT;
	if (check_buf == UP)
	{
		// printf("\n%s\n", data_processing->command_line);
		processing_button(data_processing, UP);
		// printf("up\n");
	}
	else if (check_buf == DOWN)
	{
		processing_button(data_processing, DOWN);
		// printf("down\n");
	}
	else if (check_buf == DEL)
	{
		processing_del(&data_processing->command_line, &data_processing->num_symbol);
	}
	else if (check_buf == ENTER)					// пока что печатаем, но в дальнейшем эта страка улетит на парсинг
	{
		processing_button(data_processing, ENTER);
	}
	else if (check_buf == ISPRINT)
	{
		out = write_in_terminal_isprint(data_processing);
	}
	return (out);
}

int		infinite_round()
{
	t_data_processing	*data_processing;
	int		l;

	data_processing = init_data_processing();
	if (data_processing == NULL)
	{
		return (ERROR_MALLOC);
	}
	while (1)
	{
		l = read(0, data_processing->buf_read, 10);
		if (l != 0)
		{
			input_processing(data_processing);
		}
		ft_bzero(data_processing->buf_read, 10);
	}
}

int		termcap()
{

	struct termios	term;

	if (get_term_param(&term) != 1)
	{
		// ERROR
	}
	write(1, "<minishell>$", 12);
	tputs(tgetstr("sc", 0), 1, ft_putint);						// сохранили позицию каретки
	infinite_round();
	return (1);
}