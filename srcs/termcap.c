#include "./includes/types.h"
#include "term.h"
#include "includes/lexer.h"

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

static int	input_processing(char *str, char *command_line)
{
	char	*temp;

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
		printf("del\n");
	}
	else if (str[0] == 10) // пока что печатаем, но эта страка улетит на парсинг
	{
		write(1, command_line, ft_strlen(command_line));
		write(1, "\n", 1);
		free(command_line);
		command_line = (char *)ft_calloc(1, 1);
	}
	else
	{
		// printf("код = %d\n", str[0]);
		// printf("%s\n", str);
		temp = command_line;
		command_line = ft_strjoin(temp, str);
		free(temp);
		temp = NULL;
	}
	return (1);
}

int		termcap()
{
	char	*str;
	int		l;
	struct termios term;
	char	*command_line;

	if (get_term_param(&term) != 1)
	{
		// ERROR
	}
	str = (char *)ft_calloc(1, 10);
	command_line = (char *)ft_calloc(1, 1);
	while (1)
	{
		l = read(0, str, 100);
		if (l != 0)
		{
			input_processing(str, command_line);
		}
	}
	return (1);
}