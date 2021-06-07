#include "includes/env.h"
#include <string.h>

size_t	env_length(char **env)
{
	size_t	len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

size_t	equals_position(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	*set_key(char *env_str)
{
	size_t	eq_pos;

	eq_pos = equals_position(env_str);
	return (ft_substr(env_str, 0, eq_pos));
}

char	*set_value(char *env_str)
{
	size_t		eq_pos;

	eq_pos = equals_position(env_str);
	return (ft_substr(env_str, ++eq_pos, ft_strlen(env_str)));
}

t_env_list	*find_by_key(t_env_list **env, char *key)
{
	t_env_list	*start;

	start = *env;
	while (start)
	{
		if (ft_strcmp(start->key, key) == 0)
			break ;
		start = start->next;
	}
	return (start);
}

//Хз надо ли вообще
t_env_list	*find_by_value(t_env_list **env, char *value)
{
	t_env_list	*start;

	start = *env;
	while (start)
	{
		if (ft_strcmp(start->value, value) == 0)
			break ;
		start = start->next;
	}
	return (start);
}

int	set_env_elem(int code, t_env_list **env, char *key)
{
	t_env_list	*elem;

	elem = find_by_key(env, key);
	free(elem->value);
	elem->value = ft_strdup(ft_itoa(code));
	if (elem->value == NULL)
		return (ERROR_MALLOC);
	return (OK);
}
