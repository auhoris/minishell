#include <unistd.h>
#include <stdlib.h>
#include "../includes/types.h"

void	ctrl_d(t_data_processing *g_data_processing)
{
	if (*(g_data_processing->command_line) == '\0')
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}
