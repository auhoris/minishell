#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <unistd.h>
#include <stdlib.h>

void		clear_history(t_history **start)
{
	t_history	*tmp;

	while (*start != NULL)
	{
		tmp = (*start)->next;
		free((*start)->command);
		(*start)->command = NULL;
		free((*start)->prev);
		(*start)->prev = NULL;
		free(*start);
		*start = tmp;
	}
}

int	create_start_history(t_history **start, t_history **actual, char *command_line)
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

int	create_new_element(t_history **start, t_history **actual, char *command_line)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	new->command = ft_strdup(command_line);
	if (new->command == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	new->next = NULL;
	new->prev = *actual;
	(*actual)->next = new;
	*actual = (*actual)->next;
	return (OUT);
}

// int	add_history(t_history **start, t_history **actual, char *command_line)
// {

// 	// new->next
// 	while (actual->prev != NULL)
// 	{
// 		actual = actual->prev;
// 	}
// 	actual->command = ft_strdup(command_line);
// 	if (actual->command == NULL)
// 	{
// 		clear_history(start);
// 		return (ERROR_MALLOC);

// }
// 	}

int	update_command_line(t_history *tmp, t_history **start, char *command_line)
{
	free(tmp->command);
	tmp->command = ft_strdup(command_line);
	if (tmp->command == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

int	get_up(t_history **start, t_history **actual, char *command_line)
{
	t_history *tmp;

	tmp = *actual;
	if (tmp->prev != NULL)
	{
		if (tmp->next == NULL)
		{
			if (create_new_element(start, actual, command_line) == ERROR_MALLOC)
				return (ERROR_MALLOC);
		}
		if (update_command_line(tmp, start, command_line) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		tmp = tmp->prev;
	}
	return (OUT);
}

int	get_down(t_history **start, t_history **actual, char *command_line)
{
	t_history *tmp;

	tmp = *actual;
	if (tmp->next != NULL)
	{
		if (update_command_line(tmp, start, command_line) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		tmp = tmp->next;
	}
	return (OUT);
}

int	get_history_list(t_data_processing *data_processing, int button)
{
	int	out;

	if (data_processing->start_history == NULL)
	{
		out = create_start_history(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
		if (out == ERROR_MALLOC)
			return (out);
	}
	if (button == UP)
	{
		out = get_up(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
	}
	else if (button == DOWN)
	{
		out = get_down(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
	}
	else if (button == ENTER)
	{
		out = create_new_element(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
	}
	return (out);
}