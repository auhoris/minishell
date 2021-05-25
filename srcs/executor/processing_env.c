#include "../includes/env.h"
#include "../includes/errors.h"
#include "../includes/types.h"
#include "../../libs/libft/srcs/libft.h"

int	get_pwd_dir(t_env_list *env, char **pwd_dir)
{
	while (env != NULL && ft_strcmp(env->key, "PWD") != 0)
	{
		env = env->next;
	}
	if (env == NULL)
		return (ERROR_ENV);
	*pwd_dir = ft_strdup(env->value);
	if (*pwd_dir == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}

int	set_pwd_dir(t_env_list *env, char *pwd_dir)
{
	while (env != NULL && ft_strcmp(env->key, "PWD") == 0)
	{
		env = env->next;
	}
	if (env == NULL)
		return (ERROR_ENV);
	free(env->value);
	env->value = ft_strdup(pwd_dir);
	if (env->value == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}