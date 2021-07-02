#include "../../libs/libft/srcs/libft.h"
#include "../includes/env.h"

void	write_export(t_env_list *env, int last)
{
	(void)last;
	ft_putstr("declare -x ");
	ft_putstr(env->key);
	if (env->value != NULL)
	{
		ft_putchar('=');
		ft_putchar('"');
		ft_putstr(env->value);
		ft_putchar('"');
	}
	ft_putchar('\n');
}
