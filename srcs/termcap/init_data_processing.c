#include "../includes/types.h"
#include "../../libs/libft/srcs/libft.h"
#include <stdlib.h>

t_data_processing	*init_data_processing(t_env_list *env)
{
	t_data_processing	*g_data_processing;

	g_data_processing = (t_data_processing *)malloc(sizeof(t_data_processing));
	if (g_data_processing == NULL)
	{
		return (NULL);
	}
	g_data_processing->actual_history = NULL;
	g_data_processing->start_history = NULL;
	g_data_processing->permission_create = 1;
	g_data_processing->env = env;
	g_data_processing->buf_read = (char *)ft_calloc(10, 1);
	g_data_processing->command_line = (char *)ft_calloc(1, 1);
	if (g_data_processing->buf_read == NULL
		|| g_data_processing->command_line == NULL)
	{
		free(g_data_processing->buf_read);
		free(g_data_processing->command_line);
		free(g_data_processing);
		return (NULL);
	}
	g_data_processing->num_symbol = 0;
	g_data_processing->ex_st = OK;
	g_data_processing->n_flag = FALSE;
	return (g_data_processing);
}

int	check_buf_read(char *buf_read)
{
	if (!ft_strncmp(buf_read, ARROW_UP, ft_strlen(buf_read)))
		return (UP);
	else if (!ft_strncmp(buf_read, ARROW_DOWN, ft_strlen(buf_read)))
		return (DOWN);
	else if (buf_read[0] == '\177')
		return (DEL);
	else if (buf_read[0] == 10)
		return (ENTER);
	else if (buf_read[0] == '\4')
		return (CTRL_D);
	else if (ft_isprint(buf_read[0]))
	{
		while (*buf_read)
		{
			if (ft_isprint(*buf_read) == 0)
				return (OUT);
			buf_read++;
		}
		return (ISPRINT);
	}
	return (OUT);
}
