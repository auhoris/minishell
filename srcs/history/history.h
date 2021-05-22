#ifndef HISTORY_H
# define HISTORY_H

# include "../includes/types.h"
# include "../includes/errors.h"
# include "../../libs/libft/srcs/libft.h"
# include <stdlib.h>
# include <unistd.h>

int		get_enter(t_history **start, t_history **actual,
			t_data_processing *data_processing);
int		get_up(t_history **start, t_history **actual,
			t_data_processing *data_processing);
int		get_down(t_history **start, t_history **actual,
			t_data_processing *data_processing);
void	clear_history(t_history **start);
int		create_empty_elem(t_history **start, t_history **actual);
int		update_command_list(t_history **start, t_history **actual,
			char *command_line);
int		update_command_line(t_history **start, t_history **actual,
			t_data_processing *data_processing);
void	get_last_element(t_history **actual);

#endif