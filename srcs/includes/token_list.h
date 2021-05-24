#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

# include "token.h"
# include "../../libs/libft/srcs/libft.h"
# include <stdlib.h>

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

t_token_list	*list_new_token(t_token *token);
void			list_push_back(t_token_list **head, t_token_list *new_elem);
void			print_list_info(t_token_list **head);

#endif /* ifndef TOKEN_LIST_H */
