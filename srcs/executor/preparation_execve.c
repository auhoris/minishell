#include "../includes/ast.h"
#include "../../libs/libft/srcs/libft.h"
#include "../includes/types.h"
#include "executor.h"

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

static void	bad_command(char *command)
{
	write(1, "\n", 1);
	ft_putstr("minishell: ");
	ft_putstr(command);
	ft_putstr(": command not found");
}

char	**create_args(t_ast *node)
{
	char	**args;
	size_t		i;

	args = (char **)malloc(sizeof(char *) * (node->argc + 2));
	if (args == NULL)
		return (NULL);
	args[node->argc + 1] = NULL;
	// printf("\ntest\n");
	// printf("\n%s\n", node->cmd_name);
	args[0] = ft_strdup(search_bin(node->cmd_name));
	if (args[0] == NULL)
	{
		// printf("\ntest\n");
		free(args);
		// printf("\ntest\n");
		bad_command(node->cmd_name);
		return (NULL);
	}
	i = 1;
	while (i <= node->argc)
	{
		args[i] = ft_strdup(node->argv[i - 1]);
		// printf("\n%s\n", args[i]);
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
			return(NULL);
		}
		env = env->next;
		len++;
	}
	return (envp);
}
