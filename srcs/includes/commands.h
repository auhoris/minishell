#ifndef COMMANDS_H
#define COMMANDS_H

# include <stdlib.h>
# include "../../libs/libft/srcs/libft.h"

typedef struct s_args
{
	size_t	number_of_agrs;
	char	**args_value;
	char	**flags;
}			t_args;

typedef struct s_cmd_talbe
{
	size_t	number_of_cmds;
	char	*cmd_name;
	t_args	*args;
	char	*input_file;
	char	*out_file;
	char	*err_file;
}			t_cmd_table;

t_cmd_table	*init_commands(char *command);

#endif /* ifndef COMMANDS_H */
