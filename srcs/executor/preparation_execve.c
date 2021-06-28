#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/exit_status.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "executor.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

void	free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

//Я не разобрался почему, но твоя функция почему-то не чистила всё
void	clear_array(char **args, int index)
{
	if (index == ALL_ARRAY)
	{
		while (*args != NULL)
		{
			free(*args);
			args++;
		}
	}
	else
	{
		while (index >= 0)
		{
			free(args[index]);
			index--;
		}
		free(args);
	}
}

static void	bad_command(t_exec *exec, char *command)
{
	data_processing->ex_st = EXIT_NOT_FOUND;
	ft_putchar_fd('\n', exec->tempout);
	ft_putstr_fd("minishell: ", exec->tempout);
	ft_putstr_fd(command, exec->tempout);
	if (exec->root->table_size > 1 && exec->i + 1 != exec->node->table_size)
		ft_putstr_fd(": command not found", exec->tempout);
	else
		ft_putstr_fd(": command not found\n", exec->tempout);
}

char	**create_args(t_exec *exec, t_ast *node, int *error)
{
	char		**args;
	char		*bin;
	size_t		i;

	args = (char **)malloc(sizeof(char *) * (node->argc + 2));
	if (args == NULL)
		return (NULL);
	args[node->argc + 1] = NULL;
	bin = search_bin(node->cmd_name);
	if (bin == NULL)
	{
		free(bin);
		free(args);
		bad_command(exec, node->cmd_name);
		*error = ERROR_BAD_COMMAND;
		return (NULL);
	}
	args[0] = ft_strdup(bin);
	free(bin);
	if (args[0] == NULL)
	{
		free(args);
		return (NULL);
	}
	i = 1;
	while (i <= node->argc)
	{
		args[i] = ft_strdup(node->argv[i - 1]);
		if (args[i] == NULL)
		{
			clear_array(args, i);
			return (NULL);
		}
		i++;
	}
	return (args);
}

char	**create_env(t_env_list *env)
{
	char	**envp;
	char	*tmp;
	int		len;

	len = env_lstsize(&env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		return (NULL);
	envp[len] = NULL;
	len = 0;
	while (env != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		envp[len] = ft_strjoin(tmp, env->value);
		free(tmp);
		if (envp[len] == NULL)
		{
			clear_array(envp, len);
			return (NULL);
		}
		env = env->next;
		len++;
	}
	return (envp);
}
