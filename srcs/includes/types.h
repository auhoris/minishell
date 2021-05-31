#ifndef TYPES_H
# define TYPES_H

# define ARROW_UP "\e[A"
# define ARROW_DOWN "\e[B"
# define OUT 5
# define ISPRINT 4
# define ENTER 3
# define DEL 2
# define UP 1
# define DOWN 0
# define ALL_ARRAY -1
# define BUFFER_SIZE 10

# include "env.h"

typedef struct s_history
{
	char				*command;
	struct s_history	*next;
	struct s_history	*prev;

}				t_history;

typedef struct s_data_processing
{
	int					l;
	char				*buf_read;
	char				*command_line;
	int					num_symbol;
	int					permission_create;
	t_env_list			*env;
	t_history			*start_history;
	t_history			*actual_history;

}				t_data_processing;

#endif
