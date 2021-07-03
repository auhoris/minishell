#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "termcap.h"
#include <stdlib.h>
#include <term.h>

int	write_in_terminal_isprint(t_data_processing *g_data_processing)
{
	char	*temp;
	int		out;

	out = make_history(g_data_processing);
	if (out != OUT)
		return (out);
	write(1, g_data_processing->buf_read,
		ft_strlen(g_data_processing->buf_read));
	temp = g_data_processing->command_line;
	g_data_processing->command_line = ft_strjoin(temp,
			g_data_processing->buf_read);
	free(temp);
	g_data_processing->num_symbol += ft_strlen(g_data_processing->buf_read);
	return (OUT);
}

void	write_in_terminal(char *command, int *num_symbol)
{
	if (command == NULL)
	{
		write(1, "\0", 1);
		return ;
	}
	write(1, command, ft_strlen(command));
	(*num_symbol) = ft_strlen(command);
}
