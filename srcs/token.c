#include "includes/token.h"
#include <stdlib.h>
#include <stdio.h>

t_token	*init_token(int type, char *value, int f_space)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->e_type = type;
	token->value = value;
	token->number_of_tokens = 0;
	token->f_space = f_space;
	return (token);
}

void		destroy_token(t_token *token)
{
	if (token->e_type != TOKEN_EOF)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		if (token)
		{
			free(token);
			token = NULL;
		}
	}
}
