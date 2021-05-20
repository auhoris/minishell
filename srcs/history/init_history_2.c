#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	clear_history(t_history **start)
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

static int	create_start_history(t_history **start, t_history **actual, char *command_line)
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

// static int	create_new_element(t_history **start, t_history **actual, char *command_line)
// {
// 	t_history	*new;

// 	if (*command_line == '\0')
// 		return (OUT);
// 	new = (t_history *)malloc(sizeof(t_history));
// 	if (new == NULL)
// 	{
// 		clear_history(start);
// 		return (ERROR_MALLOC);
// 	}
// 	new->command = ft_strdup(command_line);
// 	if (new->command == NULL)
// 	{
// 		clear_history(start);
// 		return (ERROR_MALLOC);
// 	}
// 	new->next = NULL;
// 	while ((*actual)->next != NULL)
// 	{
// 		(*actual) = (*actual)->next;
// 	}
// 	new->prev = *actual;
// 	(*actual)->next = new;
// 	*actual = new;
// 	return (OUT);
// }

static int	create_empty_elem(t_history **start, t_history **actual)
{
	t_history	*new;

	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	new->command = ft_calloc(1, 1);
	if (new->command == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	new->next = NULL;
	while ((*actual)->next != NULL)
		*actual = (*actual)->next;
	new->prev = *actual;
	(*actual)->next = new;
	*actual = new;
	return (OUT);
}

static int	update_command_list(t_history **start, t_history **actual, char *command_line)
{
	free((*actual)->command);
	(*actual)->command = ft_strdup(command_line);
	if ((*actual)->command == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

static int	update_command_line(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	free(data_processing->command_line);
	data_processing->command_line = ft_strdup((*actual)->command);
	if (data_processing->command_line == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	data_processing->num_symbol = 12 + ft_strlen((*actual)->command);
	return (OUT);
}

static void	get_last_element(t_history **actual)
{
	while ((*actual)->next != NULL)
		*actual = (*actual)->next;
}

static int	get_enter(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	// data_processing = NULL;
	// printf("\n%s\n", (*actual)->command);
	if (*data_processing->command_line != '\0')
	{
		if (update_command_list(start, actual, data_processing->command_line) != OUT)
			return (ERROR_MALLOC);
		if (create_empty_elem(start, actual) != OUT)
			return (ERROR_MALLOC);
	}
	else
		get_last_element(actual);
	return (OUT);
}

static int	get_up(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	if ((*actual)->prev != NULL)
	{
		// if (update_command_list(start, actual, data_processing->command_line) == ERROR_MALLOC)
		// 	return (ERROR_MALLOC);
		// printf("\n%s\n", (*actual)->command);
		(*actual) = (*actual)->prev;
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

static int	get_down(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	// printf("\ntest\n");
	if ((*actual)->next != NULL)
	{
		// pause();
		// if (update_command_list(start, actual, data_processing->command_line) == ERROR_MALLOC)
		// 	return (ERROR_MALLOC);
		(*actual) = (*actual)->next;
		// printf("\n%s\n", (*actual)->command);
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

int	get_history_data(t_data_processing *data_processing, int button)
{
	int	out;

	out = OUT;
	if (button == ENTER)
	{
		// printf("\n%s\n", data_processing->actual_history->command);
		out = get_enter(&data_processing->start_history, &data_processing->actual_history, data_processing);
	}
	else if (button == UP)
	{
		// printf("\n%s\n", data_processing->actual_history->command);
		out = get_up(&data_processing->start_history, &data_processing->actual_history, data_processing);
		// printf("\n%s\n", data_processing->command_line);
		// printf("\n%s\n", data_processing->actual_history->command);
	}
	else if (button == DOWN)
	{
		// printf("\ntest\n");
		out = get_down(&data_processing->start_history, &data_processing->actual_history, data_processing);
	}
	return (out);
}

int	make_history(t_data_processing *data_processing)
{
	int	out;

	if (data_processing->start_history == NULL)
	{
		out = create_start_history(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
		if (out == ERROR_MALLOC)
			return (out);
		// printf("\n%s\n", data_processing->actual_history->command);
	}
	// else if (data_processing->permission_create == 1)
	// {
	// 	out = create_new_element(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
	// }
	data_processing->permission_create = 0;
	return (OUT);
}