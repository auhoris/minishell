#ifndef TERMCAP_H
# define TERMCAP_H

# include "../includes/types.h"

t_data_processing	*init_data_processing(void);
int					check_buf_read(char	*buf_read);
int					write_in_terminal_isprint(t_data_processing *data_processing);
// int					get_history_list(t_data_processing *data_processing, int button);
void				write_in_terminal(char *command, int *num_symbol);
int	make_history(t_data_processing *data_processing);
int	get_history_data(t_data_processing *data_processing, int button);

#endif