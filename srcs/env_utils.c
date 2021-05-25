#include "includes/env.h"

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
