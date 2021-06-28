#include "../../libs/libft/srcs/libft.h"
#include "../includes/env.h"
#include "../includes/types.h"

static t_env_list	*create_env(t_env_list *env, t_env_list **copy_env)
{
	t_env_list	*new_elem;
	int			null_value;

	new_elem = (t_env_list *)malloc(sizeof(t_env_list));
	if (new_elem == NULL)
		return (NULL);
	new_elem->key = ft_strdup(env->key);
	if (env->value == NULL)
	{
		null_value = 1;
		new_elem->value = NULL;
	}
	else
	{
		null_value = 0;
		new_elem->value = ft_strdup(env->value);
	}
	if (new_elem->key == NULL || (new_elem->value == NULL && null_value == 0))
	{
		env_list_clear(copy_env);
		return (NULL);
	}
	return (new_elem);
}

static int		copy_env_lst(t_env_list *env, t_env_list **copy_env)
{
	t_env_list *tmp;
	t_env_list *new_elem;
	int			null_value;

	// *copy_env = (t_env_list *)malloc(sizeof(t_env_list));
	// if (*copy_env == NULL)
	// 	return (ERROR_MALLOC);
	*copy_env = NULL;
	null_value = 0;
	while (env != NULL)
	{
		if (*copy_env == NULL)
		{
			*copy_env = create_env(env, copy_env);
			if (*copy_env == NULL)
				return (ERROR_MALLOC);
			tmp = *copy_env;
		}
		else
		{
			new_elem = create_env(env, copy_env);
			if (new_elem == NULL)
				return (ERROR_MALLOC);
		}
		tmp->next = new_elem;
		tmp = tmp->next;
		env = env->next;
	}
	return (OUT);
}

static void	write_export(t_env_list *env, int last)
{
	ft_putchar('\n');
	ft_putstr("declare -x ");
	ft_putstr(env->key);
	if (env->value != NULL)
	{
		ft_putchar('=');
		ft_putchar('"');
		ft_putstr(env->value);
		ft_putchar('"');
	}
	if (last == 0)
		write(1, "\n", 1);
}

void	delete_env_elem(t_env_list *elem, t_env_list **copy_env)
{
	t_env_list *tmp;
	t_env_list *iter;

	if (ft_strcmp((*copy_env)->key, elem->key) == 0)
	{
		tmp = (*copy_env)->next;
		free(*copy_env);
		*copy_env = tmp;
	}
	else
	{
		iter = (*copy_env);
		while (ft_strcmp(iter->next->key, elem->key) != 0)
		{
			iter = iter->next;
		}
		tmp = iter->next;
		iter->next = tmp->next;
		free(tmp);

	}
}

int		write_sort_env(t_env_list *env)
{
	t_env_list *tmp;
	t_env_list *copy_env;

	if (copy_env_lst(env, &copy_env) == ERROR_MALLOC)
		return (ERROR_MALLOC);
	while (copy_env->next != NULL)
	{
		tmp = copy_env;
		while (copy_env != NULL)
		{
			if (ft_strcmp(tmp->key, copy_env->key) != 0 && ft_strcmp(tmp->value, copy_env->value) < 0)
			{
				tmp = env;
			}
			env = env->next;
		}
		write_export(tmp, 1);
		delete_env_elem(tmp, &copy_env);
	}
	write_export(tmp, 0);
	free(copy_env);
	return (OUT);
}
