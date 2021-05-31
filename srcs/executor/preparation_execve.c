#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"

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

char	**create_args(t_ast *node)
{
	char	**args;
	size_t		i;

	args = (char **)malloc(sizeof(char *) * (node->argc + 2));
	if (args == NULL)
		return (NULL);
	args[node->argc + 1] = NULL;
	args[0] = ft_strdup("/bin/bash");
	if (args[0] == NULL)
	{
		free(args);
		return (NULL);
	}
	i = 0;
	while (i < node->argc)
	{
		args[i + 1] = ft_strdup(node->argv[i]);
		if (args[i + 1] == NULL)
		{
			clear_array(args, i);
			return (NULL);
		}
	}
	return (args);
}

char	**create_env(t_env_list *env)
{
	char	**envp;
	char	*tmp;
	int		len;

	len = 0;
	while (env != NULL)
	{
		env = env->next;
		len++;
	}
	envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (envp == NULL)
		return (NULL);
	envp[len + 1] = NULL;
	len = 0;
	while (env != NULL)
	{
		tmp = ft_strjoin(env->key, "=");
		envp[len] = ft_strjoin(tmp, env->value);
		free(tmp);
		if (envp[len] == NULL)
		{
			clear_array(envp, len);
			return(NULL);
		}
		env = env->next;
		len++;
	}
	return (envp);
}