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

int	write_enter(t_data_processing *g_data_processing)
{
	int	out;

	out = OUT;
	if (is_empty(g_data_processing->command_line) == ERROR)
		g_data_processing->n_flag = FALSE;
	g_data_processing->permission_create = 1;
	if (is_empty(g_data_processing->command_line) != ERROR)
	{
		write(1, g_data_processing->command_line,
			ft_strlen(g_data_processing->command_line));
		out = start_parsing(g_data_processing);
		if (out != OUT && out != ERROR_BAD_COMMAND && out != ERROR_PARSER)
		{
			printf("ERROR = %d\n", out);
			return (out);
		}
	}
	if (g_data_processing->n_flag == FALSE)
		ft_putstr("\n<minishell>$[1] ");
	else if (g_data_processing->n_flag == TRUE)
		ft_putstr("<minishell>$[2] ");
	g_data_processing->size_pids = 0;
	return (out);
}
