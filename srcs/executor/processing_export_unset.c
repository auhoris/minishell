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

static int	check_key_value_repeated(char *key, char *value, t_env_list *env)
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

static int	get_key_export(char *str, char **key, int *i)
{
	while (*(str + *i) != '\0' && *(str + *i) != ' ' && *(str + *i) != '=')
		(*i)++;
	*key = ft_substr(str, 0, *i);
	if (*key == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}

static int	get_value_export(char *str, char **value, int *i)
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

/* static void	put_err_msg(char *str)
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
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_inset(NOT_VALID, str[i]))
		{
			put_err_msg(str);
			return (ERROR);
		}
		i++;
	}
	return (OK);
} */

int	set_key_value(char *str, t_env_list *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	if (get_key_export(str, &key, &i) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	if (get_value_export(str, &value, &i) == ERROR_MALLOC)
	{
		free(key);
		return (ERROR_MALLOC);
	}
	if (check_export(key) == ERROR)
	{
		value_key_free(value, key, NULL);
		return (ERROR);
	}
	if (check_key_value_repeated(key, value, env) != OUT)
	{
		free(key);
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
