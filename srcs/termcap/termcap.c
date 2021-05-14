#include "../includes/types.h"
#include "term.h"
#include "../includes/lexer.h"

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
	if (*num_symbol > 12)
	{
		tputs(tgetstr("le", 0), 1, ft_putint); // смещение каретки на 1 влево
		tputs(tgetstr("dc", 0), 1, ft_putint); // удаление символа
		(*num_symbol)--;
	}
	return (1);
}

static int	input_processing(char *str, char **command_line, int *num_symbol)
{
	char	*temp;

	// command_line = NULL;
	if (!ft_strncmp(str, ARROW_UP, ft_strlen(str)))
	{
		printf("up\n");
	}
	else if (!ft_strncmp(str, ARROW_DOWN, ft_strlen(str)))
	{
		printf("down\n");
	}
	else if (str[0] == '\177')
	{
		processing_del(command_line, num_symbol);
	}
	else if (str[0] == 10)					// пока что печатаем, но в дальнейшем эта страка улетит на парсинг
	{
		screen_clear();
		write(1, *command_line, ft_strlen(*command_line));
		write(1, "\n<minishell>$", 13);
		tputs(tgetstr("sc", 0), 1, ft_putint);						// сохранили позицию каретки
		free(*command_line);
		*command_line = (char *)ft_calloc(1, 1);
		*num_symbol = 12;
	}
	else if (ft_isprint(str[0]))
	{
		write(1, str, ft_strlen(str));
		temp = *command_line;
		*command_line = ft_strjoin(temp, str);
		free(temp);
		(*num_symbol) += ft_strlen(str);
	}
	else
	{
	}
	return (1);
}

int		infinite_round()
{
	int		l;
	char	*str;
	char	*command_line;
	int		num_symbol;

	str = (char *)ft_calloc(10, 1);
	command_line = (char *)ft_calloc(1, 1);
	if (str == NULL || command_line == NULL)
	{
		printf("ERROR\n");
		return (0);
	}
	num_symbol = 12;
	while (1)
	{
		l = read(0, str, 10);
		if (l != 0)
		{
			input_processing(str, &command_line, &num_symbol);
		}
		ft_bzero(str, 10);
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