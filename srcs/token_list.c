#include "includes/token_list.h"
#include <stdio.h>

t_token_list	*list_new_token(t_token *token)
{
	t_token_list	*elem;

	elem = (t_token_list *)malloc(sizeof(t_token_list));
	if (elem == NULL)
		NULL;
	elem->token = token;
	elem->next = NULL;
	return (elem);
}

void	list_push_back(t_token_list **head, t_token_list *new_elem)
{
	t_token_list	*save;

	save = *head;
	if ((*head) == NULL)
	{
		*head = new_elem;
		return ;
	}
	while (save->next)
		save = save->next;
	save->next = new_elem;
}
