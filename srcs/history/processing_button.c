#include "history.h"

int	get_enter(t_history **start, t_history **actual,
		t_data_processing *data_processing)
{
	if (*data_processing->command_line != '\0')
	{
		if ((*actual)->next == NULL)
		{
			if (update_command_list(start, actual,
					data_processing->command_line) != OUT)
				return (ERROR_MALLOC);
		}
		else
		{
			get_last_element(actual);
			if (update_command_list(start, actual,
					data_processing->command_line) != OUT)
				return (ERROR_MALLOC);
		}
		if (create_empty_elem(start, actual) != OUT)
			return (ERROR_MALLOC);
	}
	else
		get_last_element(actual);
	return (OUT);
}

int	get_up(t_history **start, t_history **actual,
		t_data_processing *data_processing)
{
	// printf("\n2|%s|\n", (*start)->command);
	if ((*actual)->prev != NULL)
	{
		(*actual) = (*actual)->prev;
		// printf("\n%s\n", (*actual)->command);
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

int	get_down(t_history **start, t_history **actual,
		t_data_processing *data_processing)
{
	if ((*actual)->next != NULL)
	{
		(*actual) = (*actual)->next;
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}
