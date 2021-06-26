#include "../../libs/libft/srcs/libft.h"
#include "../includes/env.h"

void	write_export(t_env_list *env)
{
	ft_putchar('\n');
	while (env->next != NULL)
	{
		ft_putstr("declare -x ");
		ft_putstr(env->key);
		ft_putchar('=');
		ft_putchar('"');
		ft_putstr(env->value);
		ft_putchar('"');
		write(1, "\n", 1);
		env = env->next;
	}
	ft_putstr("declare -x");
	ft_putstr(env->key);
	ft_putstr(env->value);
}
