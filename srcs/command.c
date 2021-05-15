#include "includes/commands.h"

t_cmd_table	*init_commands(char *command)
{
	t_cmd_table	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd_table));
	cmd->cmd_name = command;
	cmd->err_file = NULL;
	cmd->input_file = NULL;
	cmd->out_file = NULL;
	cmd->args->args_value = NULL;
	cmd->args->flags = NULL;
	cmd->args->number_of_agrs = 0;
	return (cmd);
}
