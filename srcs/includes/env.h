#ifndef ENV_H
# define ENV_H

typedef struct s_env_dict
{
	char	*key;
	char	*value;
}		t_env_dict;

t_env_dict	*init_env(char **env);
#endif /* ifndef ENV_H */
