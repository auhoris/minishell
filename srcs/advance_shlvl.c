#include "includes/minishell.h"

int	advance_shlvl(t_env_list **env)
{
	t_env_list	*start;
	int		shlvl;

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
