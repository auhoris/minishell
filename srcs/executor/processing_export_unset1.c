#include "executor.h"
#include "../includes/types.h"
#include "../includes/errors.h"
#include "../../libs/libft/srcs/libft.h"
#include <unistd.h>

#define NOT_VALID "-!%+.,/?:@^{}~"

static void	put_err_msg(char *str, int pos)
{
	g_data_processing->n_flag = FALSE;
	g_data_processing->n_state = TRUE;
	g_data_processing->ex_st = 1;
	if (pos != 0)
		ft_putchar_fd('\n', STDERR_FILENO);
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
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
	if (!str[i] || str[i] == '=')
		return (ERROR);
	if (ft_isdigit(str[i]))
		return (ERROR);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_inset(NOT_VALID, str[i]))
			return (ERROR);
		i++;
	}
	return (OK);
}

int	set_key_value(char *str, t_env_list *env, int pos)
{
	char	*key;
	char	*value;
	int		i;

	if (check_export(str) == ERROR)
	{
		put_err_msg(str, pos);
		return (ERROR);
	}
	i = 0;
	if (get_key_export(str, &key, &i) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	if (get_value_export(str, &value, &i) == ERROR_MALLOC)
	{
		free(key);
		return (ERROR_MALLOC);
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
