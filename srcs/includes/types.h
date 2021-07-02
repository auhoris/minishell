#ifndef TYPES_H
# define TYPES_H

# define ARROW_UP "\e[A"
# define ARROW_DOWN "\e[B"
# define OUT 0
# define DOWN 8
# define CTRL_D 7
# define VALUE_REPEATED 6
# define ISPRINT 4
# define ENTER 3
# define DEL 2
# define UP 1
# define ALL_ARRAY -1
# define BUFFER_SIZE 10
# define LAST 1

# include <term.h>
# include "env.h"

typedef struct s_history
{
	char				*command;
	struct s_history	*next;
	struct s_history	*prev;

}				t_history;

typedef struct s_data_processing
{
	int					n_flag;
	int					cmd_i;
	unsigned int		ex_st;
	int					l;
	char				*buf_read;
	char				*command_line;
	int					num_symbol;
	int					permission_create;
	struct termios		*term;
	struct termios		*term_default;
	size_t				size_pids;
	t_env_list			*env;
	t_history			*start_history;
	t_history			*actual_history;
}				t_data_processing;

#endif
