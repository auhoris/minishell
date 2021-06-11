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
	while (env != NULL && ft_strcmp(env->key, "PWD") != 0)
	{
		env = env->next;
	}
	free(env->value);
	// printf("\n%s\n", pwd_dir);
	env->value = ft_strdup(pwd_dir);
	if (env->value == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}

static int	create_old_pwd_list(t_env_list *start, char *old_pwd_dir)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (new == NULL)
		return (ERROR_MALLOC);
	new->key = ft_strdup("OLDPWD");
	new->value = ft_strdup(old_pwd_dir);
	new->next = NULL;
	if (new->key == NULL || new->value == NULL)
		return (ERROR_MALLOC);
	while (start->next != NULL)
	{
		start = start->next;
	}
	start->next = new;
	return (OUT);
}

int	set_old_pwd_dir(t_env_list *env, char *old_pwd_dir)
{
	t_env_list	*start;

	start = env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			break ;
		env = env->next;
	}
	if (env == NULL)
	{
		if (create_old_pwd_list(start, old_pwd_dir) == ERROR_MALLOC)
			return (ERROR_MALLOC);
	}
	else
	{
		free(env->value);
		env->value = ft_strdup(old_pwd_dir);
		if (env->value == NULL)
			return (ERROR_MALLOC);
	}
	return (OUT);
}