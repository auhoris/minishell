#include <stdlib.h>
#include <sys/_types/_size_t.h>
#include <sys/wait.h>
#include <term.h>
#include <unistd.h>
#include "termcap.h"
#include "../includes/minishell.h"
#include "../includes/types.h"
#include "../includes/lexer.h"
#include "../includes/parser.h"
#include "../includes/visitor.h"
#include "../includes/env.h"
#include "../executor/executor.h"

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
	return (OUT);
}

int		check_parser(t_parser *paser)
{
	int	type;

	type = paser->cur_tok->e_type;
	if (type == TOKEN_SEMI)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `;'", STDERR_FILENO);
		return (ERROR);
	}
	if (type == TOKEN_PIPE)
	{
		ft_putstr_fd("\nminishell: syntax error near unexpected token `|'", STDERR_FILENO);
		return (ERROR);
	}
	return (OK);
}

static int	wait_pids(t_exec *exec)
{
	size_t	i;
	int		waiting;
	int		temp;

	i = 0;
	if (exec->size_pids == 0)
		return (OK);
	write(STDIN_FILENO, "\n", 1);
	while (i < exec->size_pids)
	{
		temp = waitpid(exec->pids[i], &waiting, 0);
		if ((temp = WIFEXITED(waiting)))
		{
			exec->exit_status = WEXITSTATUS(waiting);
		}
		i++;
	}
	return (OK);
}

void	free_lexer(t_lexer *lexer)
{
	free(lexer->content);
	free(lexer);
}

void	free_parser(void *parser)
{
	free_lexer(((t_parser *)parser)->lexer);
	destroy_token(((t_parser *)parser)->cur_tok);
	free(parser);
}

void	free_root_parser(void *root)
{
	free_nodes(((t_ast *)root));
}

void	free_exec(void *exec)
{
	free(((t_exec *)exec)->pids);
	free_nodes(((t_exec *)exec)->root);
	free(exec);
}

int	free_unique(int code, void *content, void(*del)(void *))
{
	(*del)(content);
	return (code);
}

static int	start_parsing(t_data_processing *data_processing)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_ast		*root;
	int			out;
	t_exec		*exec;

	out = OUT;
	root = NULL;
	lexer = init_lexer(data_processing->actual_history->prev->command);
	parser = init_parser(lexer, data_processing->env);
	if (check_parser(parser) == ERROR || parser == NULL)
		return (free_unique(ERROR_MALLOC, parser, free_parser));
	root = parser_parse_commands(parser);
	free_parser(parser);
	if (root->err_handler != OK)
		return (free_unique(root->err_handler, root, free_root_parser));
	exec = init_exec(root);
	if (exec == NULL)
		return (free_unique(ERROR_MALLOC, exec, free_exec));
	out = detour_tree(exec, root, data_processing->env);
	data_processing->size_pids = exec->size_pids;
	data_processing->flag_echo = exec->flag_echo;
	wait_pids(exec);
	free_exec(exec);
	printf("out = %d\n", out);
	return (out);
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
		data_processing->permission_create = 1;
		if (*data_processing->command_line != '\0')
		{
			write(1, data_processing->command_line, ft_strlen(data_processing->command_line));
			out = start_parsing(data_processing);
			if (out != OUT && out != ERROR_BAD_COMMAND)
				return (out);
		}
		if (data_processing->size_pids != 0)
			write(1, "<minishell>$ ", 13);
		else if (data_processing->flag_echo == 0)
			write(1, "\n<minishell>$ ", 14);
		else
			write(1, "<minishell>$ ", 14);
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
	return (out);
}

static int		infinite_round(t_env_list *env)
{
	t_data_processing	*data_processing;
	int		l;
	int		out;

	out = OUT;
	data_processing = init_data_processing(env);
	if (data_processing == NULL)
	{
		return (ERROR_MALLOC);
	}
	while (1)
	{
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

	if (get_term_param(&term) != 1)
	{
		// ERROR
	}
	write(1, "<minishell>$ ", 13);
/*
	sc сохранение позиции каретки
*/
	tputs(tgetstr("sc", 0), 1, ft_putint);
	infinite_round(env);
	return (1);
}
