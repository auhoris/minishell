#include "history.h"

static int	create_start_history(t_history **start,
				t_history **actual, char *command_line)
{
	*start = (t_history *)malloc(sizeof(t_history));
	if (start == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	(*start)->next = NULL;
	(*start)->prev = NULL;
	(*start)->command = ft_strdup(command_line);
	if ((*start)->command == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	*actual = *start;
	return (OUT);
}

int	get_history_data(t_data_processing *data_processing, int button)
{
	int	out;

	out = OUT;
	if (button == ENTER)
	{
		out = get_enter(&data_processing->start_history,
				&data_processing->actual_history, data_processing);
	}
	else if (button == UP)
	{
		out = get_up(&data_processing->start_history,
				&data_processing->actual_history, data_processing);
	}
	else if (button == DOWN)
	{
		out = get_down(&data_processing->start_history,
				&data_processing->actual_history, data_processing);
	}
	return (out);
}

int	make_history(t_data_processing *data_processing)
{
	int	out;

	if (data_processing->start_history == NULL)
	{
		out = create_start_history(&data_processing->start_history,
				&data_processing->actual_history,
				data_processing->command_line);
		if (out == ERROR_MALLOC)
			return (out);
	}
	data_processing->permission_create = 0;
	return (OUT);
}
