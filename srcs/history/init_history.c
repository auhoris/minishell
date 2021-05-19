#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	while ((*actual)->next != NULL)
	{
		(*actual) = (*actual)->next;
	}
	new->prev = *actual;
	(*actual)->next = new;
	*actual = new;
	// printf("\n %s \n", (*actual)->command);
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

int	update_command_list(t_history **start, t_history **actual, char *command_line)
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

int	update_command_line(t_history **start, t_history **actual, t_data_processing *data_processing)
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

int	get_up(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	// t_history *tmp;

	// printf("\n%s\n", command_line);
	// tmp = *actual;
	if ((*actual)->prev != NULL)
	{
		if ((*actual)->next == NULL)
		{
			if (create_new_element(start, actual, data_processing->command_line) == ERROR_MALLOC)
				return (ERROR_MALLOC);
			// printf("\ncomand = %s\n", (*actual)->command);
		}
		if (update_command_list(start, actual, data_processing->command_line) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		(*actual) = (*actual)->prev;
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		// printf("\ncomand = %s\n", (*actual)->command);
	}
	// printf("\n %s \n", (*actual)->command);
	return (OUT);
}

int	get_down(t_history **start, t_history **actual, t_data_processing *data_processing)
{
	// t_history *tmp;

	// tmp = *actual;
	if ((*actual)->next != NULL)
	{
		if (update_command_list(start, actual, data_processing->command_line) == ERROR_MALLOC)
			return (ERROR_MALLOC);
		(*actual) = (*actual)->next;
		if (update_command_line(start, actual, data_processing) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

int	get_history_list(t_data_processing *data_processing, int button)
{
	int	out;

	// printf("\n%s\n", data_processing->command_line);
	if (button == UP && data_processing->start_history != NULL)
	{
		out = get_up(&data_processing->start_history, &data_processing->actual_history, data_processing);
	}
	else if (button == DOWN && data_processing->start_history != NULL)
	{
		out = get_down(&data_processing->start_history, &data_processing->actual_history, data_processing);
	}
	else if (button == ENTER)
	{
		if (data_processing->start_history == NULL)
		{
			// printf("\ntest\n");
			out = create_start_history(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
			if (out == ERROR_MALLOC)
				return (out);
		}
		else
			out = create_new_element(&data_processing->start_history, &data_processing->actual_history, data_processing->command_line);
	}
	return (OUT);
}