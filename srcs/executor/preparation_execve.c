#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/exit_status.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "executor.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

void	free_arr(char **arr, char **env_array)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	if (env_array == NULL)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

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

char	**create_args(t_ast *node, int *error, char **path_array)
{
	char		**args;
	char		*bin;

	args = (char **)malloc(sizeof(char *) * (node->argc + 2));
	if (args == NULL)
		return (NULL);
	args[node->argc + 1] = NULL;
	if (search_bin(&bin, node->cmd_name, path_array) == ERROR_MALLOC)
	{
		*error = ERROR_MALLOC;
		free(args);
		return (NULL);
	}
	if (path_array)
		free_arr(path_array, NULL);
	args[0] = ft_strdup(bin);
	free(bin);
	if (args[0] == NULL)
	{
		free(args);
		return (NULL);
	}
	if (fill_args(args, node) == ERROR_MALLOC)
		return (NULL);
	return (args);
}

static int	create_env1(t_env_list *env, char **envp, int len)
{
	char	*tmp;

	tmp = ft_strjoin(env->key, "=");
	if (env->value != NULL)
	{
		envp[len] = ft_strjoin(tmp, env->value);
		free(tmp);
	}
	else
		envp[len] = tmp;
	if (envp[len] == NULL)
	{
		clear_array(envp, len);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

char	**create_env(t_env_list *env)
{
	char	**envp;
	int		len;

	len = env_lstsize(&env);
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		return (NULL);
	envp[len] = NULL;
	len = 0;
	while (env != NULL)
	{
		if (create_env1(env, envp, len) == ERROR_MALLOC)
			return (NULL);
		env = env->next;
		len++;
	}
	return (envp);
}
