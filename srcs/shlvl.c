#include "includes/minishell.h"
#include "includes/exit_status.h"
#include <stddef.h>

#define RANGE 256

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

static int	keep_in_range(int number)
{
	if (number >= 0)
		return (number % RANGE);
	else
		return (RANGE - (abs(number) % RANGE));
}

static int	check_numeric(char *arg)
{
	size_t	i;

	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (ERROR);
		i++;
	}
	return (OK);
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
	if (argv)
	{
		if (check_numeric(argv[0]) != OK)
		{
			ft_putstr_fd("\nminishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[0], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required", STDERR_FILENO);
			// ft_putchar('\n');
			return (EXIT_NUMERIC);
		}
	}
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
	if (argv != NULL)
		data_processing->ex_st = keep_in_range(ft_atoi(argv[0]));
	return (ERROR_EXIT);
}
