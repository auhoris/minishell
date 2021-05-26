#include "../includes/env.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"

static void	value_key_free(char *value, char *key, t_env_list *new)
{
	free(value);
	free(key);
	free(new);
}

static int	create_new_env(char *key, char *value, t_env_list *env)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (new == NULL)
		return (ERROR_MALLOC);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->key == NULL || new->value == NULL)
	{
		value_key_free(new->value, new->key, new);
		return (ERROR_MALLOC);
	}
	new->next = NULL;
	while (env->next != NULL)
	{
		env = env->next;
	}
	env->next = new;
	return (OUT);
}

int	set_key_value(char *str, t_env_list *env)
{
	char	*chr;
	char	*key;
	char	*value;
	int		len;

	while (env->next != NULL)
		env = env->next;
	chr = ft_strchr(str, '=');
	if (chr == NULL)
		return (OUT);
	len = chr - str;
	key = ft_substr(str, 0, len);
	value = ft_strdup(chr + 1);
	if (key == NULL || value == NULL)
	{
		value_key_free(value, key, NULL);
		return (ERROR_MALLOC);
	}
	if (create_new_env(key, value, env) == ERROR_MALLOC)
	{
		value_key_free(value, key, NULL);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

char	*get_value(char *str)
{
	char	*chr;
	char	*key;
	int	len;

	chr = ft_strchr(str, '=');
	len = chr - str;
	key = ft_substr(str, 0, len);
	return (key);
}

// int	set_export_variables(char *key, char *value, t_env_list *env)
// {
// 	t_env_list	*new;

// 	new = (t_env_list *)malloc(sizeof(t_env_list));
// 	if (new == NULL)
// 		return (ERROR_MALLOC);
// 	new->key = ft_strdup(key);
// 	new->value = ft_strdup(value);
// 	new->next = NULL;
// 	if (new->key == NULL || new->value == NULL)
// 		return (ERROR_MALLOC);
// 	while (env->next != NULL)
// 	{
// 		env = env->next;
// 	}
// 	env->next = new;
// 	return (OUT);
// }