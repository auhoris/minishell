#include "../includes/env.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <stddef.h>
#include <unistd.h>

#define NOT_VALID "-!%+.,/?:@^_{}~"
static void	value_key_free(char *value, char *key, t_env_list *new)
{
	free(value);
	free(key);
	free(new);
}

//Почему не сделать через env_addback?
static int	create_new_env(char *key, char *value, t_env_list *env)
{
	t_env_list	*new;

	new = env_new(ft_strdup(key), ft_strdup(value));
	if (new == NULL)
		return (ERROR_MALLOC);
	env_addback(&env, new);
	return (OUT);
}

	/* t_env_list	*new;

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
	env->next = new; */

static void	put_err_msg(char *str)
{
	ft_putstr_fd("\nminishell: export: ", STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putstr_fd(" not a valid identifier", STDERR_FILENO);
}

static int	check_export(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(str[i]))
	{
		put_err_msg(str);
		return (ERROR);
	}
	while (str[i] != '=' || str[i] != '\0')
	{
		if (ft_inset(NOT_VALID, str[i]))
		{
			put_err_msg(str);
			return (ERROR);
		}
		i++;
	}
	return (OK);
}

int	set_key_value(char *str, t_env_list *env)
{
	char	*chr;
	char	*key;
	char	*value;
	int		len;

	while (env->next != NULL)
		env = env->next;
	if (check_export(str) == ERROR)
		return (OUT);
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
	value_key_free(value, key, NULL);
	return (OUT);
}

char	*get_value(char *str)
{
	char	*chr;
	char	*key;
	int		len;

	chr = ft_strchr(str, '=');
	len = chr - str;
	key = ft_substr(str, 0, len);
	return (key);
}

int	unset_env_elem(t_env_list **env, char *key)
{
	t_env_list	*tmp;
	t_env_list	*prev;
	t_env_list	*start;

	if (!(*env))
		return (OK);
	start = *env;
	while (start)
	{
		if (ft_strcmp((start)->key, key) == 0)
		{
			prev->next = start->next;
			tmp = start;
			env_list_delone(tmp);
			return (OK);
		}
		prev = start;
		start = start->next;
	}
	return (OK);
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
