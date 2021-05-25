#include "includes/env.h"

t_env_list	*env_new(char *key, char *value)
{
	t_env_list	*env;

	env = malloc(sizeof(*env));
	if (env == NULL)
		return (NULL);
	env->key = key;
	env->value = value;
	env->next = NULL;
	return (env);
}

void	env_addback(t_env_list **head, t_env_list *env_new)
{
	t_env_list	*start;

	if (!(*head))
	{
		*head = env_new;
		return ;
	}
	start = *head;
	while (start->next)
		start = start->next;
	start->next = env_new;
}

void	env_list_delone(t_env_list *elem)
{
	if (elem == NULL)
		return ;
	free(elem->key);
	free(elem->value);
	free(elem);
}

void	env_list_clear(t_env_list **head)
{
	t_env_list	*temp;

	if (!(*head))
		return ;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		env_list_delone(temp);
	}
	*head = NULL;
}
