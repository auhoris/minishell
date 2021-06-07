#ifndef ENV_H
# define ENV_H

# include <sys/_types/_size_t.h>
# include "../../libs/libft/srcs/libft.h"
# include "token.h"
# include "utils.h"

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}			t_env_list;

t_env_list	*init_env_list(char **env);
t_env_list	*env_new(char *key, char *value);
void		env_addback(t_env_list **head, t_env_list *env_new);
void		env_list_delone(t_env_list *elem);
void		env_list_clear(t_env_list **head);
size_t		env_lstsize(t_env_list **head);
char		*get_value_by_key(t_token *token, t_env_list **env_dict);
// Utils
int			set_env_elem(int code, t_env_list **env, char *key);
t_env_list	*find_by_key(t_env_list **env, char *key);
char		*set_value(char *env_str);
char		*set_key(char *env_str);
size_t		equals_position(char *str);
size_t		env_length(char **env);
void		show_dict(t_env_list **env);

#endif /* ifndef ENV_H */
