#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "termcap.h"
#include <stdlib.h>
#include <term.h>

int	write_in_terminal_isprint(t_data_processing *data_processing)
{
	char	*temp;
	int	out;

	out = make_history(data_processing);
	if (out != OUT)
		return (out);
	write(1, data_processing->buf_read, ft_strlen(data_processing->buf_read));
	temp = data_processing->command_line;
	data_processing->command_line = ft_strjoin(temp, data_processing->buf_read);
	free(temp);
	(data_processing->num_symbol) += ft_strlen(data_processing->buf_read);
	return (OUT);
}

void	write_in_terminal(char *command, int *num_symbol)
{
	// write(1, "\n<minishell>$", 13);
	// tputs(tgetstr("sc", 0), 1, ft_putint);
	if (command == NULL)
	{
		write(1, "\0", 1);
		(*num_symbol)++;
		return ;
	}
	// write(1, "\ntest\n", 6);
	write(1, command, ft_strlen(command));
	(*num_symbol) += ft_strlen(command);
}
