#include "../includes/types.h"
#include "../../libs/libft/srcs/libft.h"
#include <stdlib.h>

t_data_processing	*init_data_processing(void)
{
	t_data_processing	*data_processing;

	data_processing = (t_data_processing *)malloc(sizeof(t_data_processing));
	if (data_processing == NULL)
	{
		return (NULL);
	}
	data_processing->actual_history = NULL;
	data_processing->start_history = NULL;
	data_processing->permission_create = 1;
	data_processing->buf_read = (char *)ft_calloc(10, 1);
	data_processing->command_line = (char *)ft_calloc(1, 1);
	if (data_processing->buf_read == NULL
		|| data_processing->command_line == NULL)
	{
		free(data_processing->buf_read);
		free(data_processing->command_line);
		free(data_processing);
		return (NULL);
	}
	data_processing->num_symbol = 0;
	return (data_processing);
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
