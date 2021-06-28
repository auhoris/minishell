#include "includes/minishell.h"

int	advance_shlvl(t_env_list **env)
{
	t_env_list	*start;
	int			shlvl;

	shlvl = ft_atoi(get_value_by_key("SHLVL", env));
	shlvl++;
	start = *env;
	while (start)
	{
		if (ft_strcmp(start->key, "SHLVL") == 0)
		{
			free(start->value);
			start->value = ft_strdup(ft_itoa(shlvl));
			if (start->value == NULL)
				return (ERROR_MALLOC);
			break ;
		}
		start = start->next;
	}
	return (ERROR_EXIT);
}

int	executor_exit(size_t argc, char **argv, t_env_list **env)
{
	t_env_list	*start;
	int			shlvl;

	ft_putstr_fd("\nexit", STDOUT_FILENO);
	if (argc > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (ERROR_EXIT_ARGC);
	}
	if (argv != NULL)
		printf("\n%s\n", argv[0]);
	shlvl = ft_atoi(get_value_by_key("SHLVL", env));
	shlvl--;
	start = *env;
	while (start)
	{
		if (ft_strcmp(start->key, "SHLVL") == 0)
		{
			free(start->value);
			start->value = ft_strdup(ft_itoa(shlvl));
			if (start->value == NULL)
				return (ERROR_MALLOC);
			break ;
		}
		start = start->next;
	}
	return (ERROR_EXIT);
}
