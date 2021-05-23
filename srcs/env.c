#include "includes/env.h"
#include "../libs/libft/srcs/libft.h"
#include <sys/_types/_size_t.h>

static size_t	env_length(char **env)
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
	size_t	eq_pos;
	static int	i;

	i++;
	eq_pos = equals_position(env_str);
	return (ft_substr(env_str, ++eq_pos, ft_strlen(env_str)));
}

char	*get_value_by_key(t_token *token, t_env_dict **env_dict)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = ft_strdup("");
	if (ret == NULL)
		return (NULL);
	while (env_dict[i])
	{
		if (ft_strcmp(env_dict[i]->key, token->value) == 0)
		{
			ret = connect_str(ret, env_dict[i]->value);
			if (ret == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	return (ret);
}

void	clear_env(t_env_dict **env_dict)
{
	size_t	i;

	i = 0;
	while (env_dict[i])
	{
		if (env_dict[i]->value)
			free(env_dict[i]->value);
		if (env_dict[i]->key)
			free(env_dict[i]->key);
		if (env_dict[i])
			free(env_dict[i]);
		i++;
	}
	free(env_dict);
}

/* void	show_dict(t_env_dict **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("%s=%s\n", env[i]->key, env[i]->value);
		i++;
	}
} */

t_env_dict	**init_env(char **env)
{
	t_env_dict	**env_dict;
	size_t		len;
	size_t		i;

	i = 0;
	len = env_length(env);
	env_dict = malloc((len + 1) * sizeof(t_env_dict*));
	if (env_dict == NULL)
		return (NULL);
	while (i < len)
	{
		env_dict[i] = malloc(sizeof(t_env_dict));
		env_dict[i]->value = set_value(env[i]);
		env_dict[i]->key = set_key(env[i]);
		if (env_dict[i] == NULL || env_dict[i]->key == NULL || env_dict[i]->value == NULL)
		{
			clear_env(env_dict);
			return (NULL);
		}
		i++;
	}
	env_dict[i] = NULL;
	return (env_dict);
}
