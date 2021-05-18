#include "includes/token.h"
#include <stdlib.h>

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

void		destroy_token(t_token *token)
{
	if (token->value)
		free(token->value);
	if (token)
		free(token);
}
