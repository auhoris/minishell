#include "../includes/types.h"
#include <term.h>
#include "../includes/lexer.h"
#include "termcap.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/ast.h"
#include "../includes/visitor.h"
#include "../includes/env.h"

static int		get_term_param(struct termios *term)
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
	if (out != 0)
	{
		// ERROR (есть errno)
	}
/*
	~(ECHO) не отображать вводимые символы
	~(ICANON) выкл канонический режим (теперь мы видим то, что вводим)
	tcsetattr(0, TCSANOW, term) - If optional_actions is TCSANOW, the change shall occur immediately (изменения произойдут немедленно).
*/
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
	return (1);
}

void	start_parsing(char *input, t_env_dict **env)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*root;
	/* t_token		*token;
	(void)env; */

	lexer = init_lexer(input);
	/* token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("type='%s'\tvalue='%s'\n", print_token_type(token->e_type), token->value);
		token = lexer_get_next_token(lexer);
	} */
	parser = init_parser(lexer, env);
	root = parser_parse_commands(parser);
	visitor_visit_nodes(root);

}
static int	processing_button(t_data_processing *data_processing, int button)
{
	int	out;

	if (data_processing->actual_history == NULL && button != ENTER)
		return (OUT);
	screen_clear();
	out = get_history_data(data_processing, button);
	if (button == ENTER)
	{
		data_processing->permission_create = 1;
		if (*data_processing->command_line != '\0')
		{
			start_parsing(data_processing->actual_history->prev->command, data_processing->env);
			// write(1, " выполнение команды ", 38);
			// write(1, data_processing->actual_history->prev->command, ft_strlen(data_processing->actual_history->prev->command));
		}
		write(1, "\n<minishell>$", 13);
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

static char	input_processing(t_data_processing *data_processing)
{
	int	check_buf;
	int	out;

	check_buf = check_buf_read(data_processing->buf_read);
	out = OUT;
	if (check_buf == UP)
	{
		processing_button(data_processing, UP);
	}
	else if (check_buf == DOWN)
	{
		processing_button(data_processing, DOWN);
	}
	else if (check_buf == DEL)
	{
		processing_del(&data_processing->command_line, &data_processing->num_symbol);
	}
	else if (check_buf == ENTER)
	{
		processing_button(data_processing, ENTER);
	}
	else if (check_buf == ISPRINT)
	{
		out = write_in_terminal_isprint(data_processing);
	}
	return (out);
}

static int		infinite_round(t_env_dict **env)
{
	t_data_processing	*data_processing;
	int		l;

	data_processing = init_data_processing(env);
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

int		termcap(t_env_dict **env)
{

	struct termios	term;

	if (get_term_param(&term) != 1)
	{
		// ERROR
	}
	write(1, "<minishell>$", 12);
/*
	sc сохранение позиции каретки
*/
	tputs(tgetstr("sc", 0), 1, ft_putint);
	infinite_round(env);
	return (1);
}
