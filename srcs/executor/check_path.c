#include "../../libs/libft/srcs/libft.h"
#include "../includes/env.h"
#include "../includes/errors.h"
#include "../includes/types.h"

int	get_path_array(t_env_list *env, char ***bin_arr)
{
	while (env && ft_strcmp(env->key, "PATH") != 0)
		env = env->next;
	if (env == NULL)
		return (NO_PATH);
	*bin_arr = ft_split(env->value, ':');
	if (*bin_arr == NULL)
		return (ERROR_MALLOC);
	return (OUT);
}
