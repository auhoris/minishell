#include "history.h"

void	clear_history(t_history **start)
{
	t_history	*tmp;
	int			i;

	i = 0;
	while ((*start)->next != NULL)
	{
		// printf("\ni = %d\n", i);
		tmp = (*start)->next;
		free((*start)->command);
		// printf("\nfree (*start)->command\n");
		(*start)->command = NULL;
		free(*start);
		*start = tmp;
		i++;
	}
}

int	create_empty_elem(t_history **start, t_history **actual)
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

int	update_command_list(t_history **start, t_history **actual,
		char *command_line)
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

int	update_command_line(t_history **start, t_history **actual,
		t_data_processing *data_processing)
{
	free(data_processing->command_line);
	data_processing->command_line = ft_strdup((*actual)->command);
	if (data_processing->command_line == NULL)
	{
		clear_history(start);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

void	get_last_element(t_history **actual)
{
	if (*actual == NULL)
		return ;
	while ((*actual)->next != NULL)
		*actual = (*actual)->next;
}
