#ifndef TERMCAP_H
# define TERMCAP_H

# include "../includes/types.h"
# include <term.h>

t_data_processing	*init_data_processing(t_env_list *env);
int					check_buf_read(char	*buf_read);
int					write_in_terminal_isprint(t_data_processing
						*data_processing);
void				write_in_terminal(char *command, int *num_symbol);
int					make_history(t_data_processing *data_processing);
int					get_history_data(t_data_processing *data_processing,
						int button);
void				error_processing(t_env_list *env, t_data_processing
						*data_processing, int error_code);
void				ctrl_d(t_data_processing *data_processing);
int					write_enter(t_data_processing *data_processing);
int					get_term_param(struct termios *term,
						struct termios *term_default);
void				screen_clear(void);

#endif
