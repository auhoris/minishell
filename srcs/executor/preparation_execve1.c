#include "../includes/ast.h"
#include "../includes/errors.h"
#include "../includes/types.h"
#include "executor.h"
#include <stdlib.h>

int	fill_args(char **args, t_ast *node)
{
	size_t	i;

	i = 1;
	while (i <= node->argc)
	{
		args[i] = ft_strdup(node->argv[i - 1]);
		if (args[i] == NULL)
		{
			clear_array(args, i);
			return (ERROR_MALLOC);
		}
		i++;
	}
	return (OUT);
}
