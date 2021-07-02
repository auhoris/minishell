#include "executor.h"
#include "../includes/env.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <stddef.h>
#include <unistd.h>

static int	create_new_env(char *key, char *value, t_env_list *env)
{
	t_env_list	*new;
	int			null_value;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (new == NULL)
		return (ERROR_MALLOC);
	new->key = ft_strdup(key);
	null_value = 0;
	if (value == NULL)
	{
		new->value = NULL;
		null_value = 1;
	}
	else
		new->value = ft_strdup(value);
	if (new->key == NULL || (new->value == NULL && null_value == 0))
	{
		value_key_free(new->value, new->key, new);
		return (ERROR_MALLOC);
	}
	new->next = NULL;
	while (env->next != NULL)
		env = env->next;
	env->next = new;
	return (OUT);
}

static int	setter_value(char *value, t_env_list *env)
{
	free(env->value);
	if (value == NULL)
		env->value = NULL;
	else
	{
		env->value = ft_strdup(value);
		if (env->value == NULL)
			return (ERROR_MALLOC);
	}
	return (OUT);
}

int	check_key_value_repeated(char *key, char *value, t_env_list *env)
{
	t_env_list	*previous;

	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (setter_value(value, env));
		previous = env;
		env = env->next;
	}
	if (create_new_env(key, value, previous) == ERROR_MALLOC)
	{
		value_key_free(value, key, NULL);
		return (ERROR_MALLOC);
	}
	return (OUT);
}

int	get_key_export(char *str, char **key, int *i)
{
	while (*(str + *i) != '\0' && *(str + *i) != ' ' && *(str + *i) != '=')
		(*i)++;
	*key = ft_substr(str, 0, *i);
	if (*key == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}

int	get_value_export(char *str, char **value, int *i)
{
	int		nul_value;

	nul_value = 0;
	if (*(str + *i) == ' ' || *(str + *i) == '\0')
	{
		*value = NULL;
		nul_value = 1;
	}
	else
		*value = ft_strdup(str + *i + 1);
	if (*value == NULL && nul_value == 0)
	{
		free(*value);
		return (ERROR_MALLOC);
	}
	return (OUT);
}
