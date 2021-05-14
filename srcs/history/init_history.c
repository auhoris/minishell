#include "../includes/types.h"
#include "../includes/errors.h"
#include <unistd.h>
#include <stdlib.h>

int		make_start_history(t_history **start)
{
	*start = (t_history *)malloc(sizeof(t_history));
	if (*start == NULL)
	{
		return (ERROR_MALLOC);
	}
	return (1);
}

int		get_history_list(t_history **start)
{
	int	out;

	if (*start == NULL)
	{
		out = make_start_history(start);
		return (out);
	}
	else
	{

	}
}