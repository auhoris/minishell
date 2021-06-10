#include "includes/env.h"
#include "../libs/libft/srcs/libft.h"
#include "includes/errors.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

char	*get_value_by_key(char *value, t_env_list **env_dict)
{
	t_env_list	*start;

	start = *env_dict;
	while (start)
	{
		if (ft_strcmp(start->key, value) == 0)
			return (start->value);
		start = start->next;
	}
	return ("");
}

void	show_dict(t_env_list **env)
{
	t_env_list	*start;

	start = *env;
	while (start)
	{
		ft_putstr(start->key);
		ft_putstr("=");
		ft_putstr(start->value);
		ft_putstr("\n");
		start = start->next;
	}
}

t_env_list	*init_env_list(char **env)
{
	t_env_list	*env_list;
	t_env_list	*temp;
	size_t		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		temp = env_new(set_key(env[i]), set_value(env[i]));
		if (temp == NULL)
		{
			env_list_clear(&env_list);
			return (NULL);
		}
		env_addback(&env_list, temp);
		i++;
	}
	return (env_list);
}
