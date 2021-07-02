#include "../includes/types.h"
#include "../includes/minishell.h"

static int	is_empty(char *line)
{
	int	i;

	if (*line == '\0')
		return (ERROR);
	i = -1;
	while (line[++i] == ' ')
		;
	if (line[i] == '\0')
		return (ERROR);
	return (OK);
}

int	write_enter(t_data_processing *data_processing)
{
	int	out;

	out = OUT;
	if (is_empty(data_processing->command_line) == ERROR)
		data_processing->n_flag = FALSE;
	data_processing->permission_create = 1;
	if (is_empty(data_processing->command_line) != ERROR)
	{
		write(1, data_processing->command_line,
			ft_strlen(data_processing->command_line));
		out = start_parsing(data_processing);
		if (out != OUT && out != ERROR_BAD_COMMAND && out != ERROR_PARSER)
		{
			printf("ERROR = %d\n", out);
			return (out);
		}
	}
	if (data_processing->n_flag == FALSE)
		ft_putstr("\n<minishell>$[1] ");
	else if (data_processing->n_flag == TRUE)
		ft_putstr("<minishell>$[2] ");
	data_processing->size_pids = 0;
	return (out);
}
