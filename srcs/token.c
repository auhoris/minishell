#include "includes/token.h"

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

void	destroy_token(t_token *token)
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

char	*print_token_type(int type)
{
	switch (type) {
		case TOKEN_ID: return ("TOKEN_ID");
		case TOKEN_BSLASH: return ("TOKEN_BSLASH");
		case TOKEN_SQUOTE: return ("TOKEN_SQUOTE");
		case TOKEN_DQUOTE: return ("TOKEN_DQUOTE");
		case TOKEN_SEMI: return ("TOKEN_SEMI");
		case TOKEN_LESS: return ("TOKEN_LESS");
		case TOKEN_MORE: return ("TOKEN_MORE");
		case TOKEN_DMORE: return ("TOKEN_DMORE");
		case TOKEN_EQUALS: return ("TOKEN_EQUALS");
		case TOKEN_PIPE: return ("TOKEN_PIPE");
		case TOKEN_DOLLAR: return ("TOKEN_DOLLAR");
		case BAD_TOKEN: return ("BAD_TOKEN");
		case TOKEN_EOF: return ("TOKEN_EOF");
		case TOKEN_CMD: return ("TOKEN_CMD");
		// case TOKEN_FLAG: return ("TOKEN_FLAG");
		default: return ("Undefined token");
	}
}
