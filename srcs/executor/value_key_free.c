#include "../includes/env.h"
#include <unistd.h>

void	value_key_free(char *value, char *key, t_env_list *new)
{
	free(value);
	free(key);
	free(new);
}
