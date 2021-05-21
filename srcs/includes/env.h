#ifndef ENV_H
# define ENV_H

# include <sys/_types/_size_t.h>
# include "../../libs/libft/srcs/libft.h"
# include <stdio.h>

typedef struct s_env_dict
{
	char	*key;
	char	*value;
}			t_env_dict;

t_env_dict	**init_env(char **env);
void		show_dict(t_env_dict **env);
/* size_t		env_length(char **env);
size_t		equals_position(char *str);
char		*ft_set_key(char *env_str):
char		*ft_set_value(char *env_str);
void		clear_env(t_env_dict **env_dict); */

#endif /* ifndef ENV_H */
