#ifndef ENV_H
# define ENV_H

# include "minishell.h"
# include <sys/_types/_size_t.h>
# include "../../libs/libft/srcs/libft.h"
# include "token.h"
# include "utils.h"

typedef struct s_env_dict
{
	char	*key;
	char	*value;
}			t_env_dict;

t_env_dict	**init_env(char **env);
void		show_dict(t_env_dict **env);
char		*get_value_by_key(t_token *token, t_env_dict **env_dict);
void		clear_env(t_env_dict **env_dict);

#endif /* ifndef ENV_H */
