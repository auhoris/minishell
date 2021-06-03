#ifndef TOKEN_H
# define TOKEN_H

# include "../../libs/libft/srcs/libft.h"
# include <sys/_types/_size_t.h>

# define TRUE 1
# define FALSE 0

typedef enum e_errors
{
	ERR_UNCLOSED_DQUOTE,
	ERR_UNCLOSED_SQUOTE,
}	t_errors;

/* TOKEN_ID, //0
TOKEN_CMD, //1
TOKEN_BSLASH, //2
TOKEN_SQUOTE, //3
TOKEN_DQUOTE, //4
TOKEN_SEMI, //5
TOKEN_LESS, //6 Работает как редирект при записи: >echo
TOKEN_MORE, //7 То же что и выше
TOKEN_DMORE, //8 То же что и выше
TOKEN_PIPE, //9
TOKEN_DOLLAR, //10
TOKEN_EQUALS, //11
BAD_TOKEN, //12
TOKEN_EOF, //13 */

typedef struct s_token
{
	enum
	{
		TOKEN_ID,
		TOKEN_CMD,
		TOKEN_BSLASH,
		TOKEN_SQUOTE,
		TOKEN_DQUOTE,
		TOKEN_SEMI,
		TOKEN_LESS,
		TOKEN_MORE,
		TOKEN_DMORE,
		TOKEN_PIPE,
		TOKEN_DOLLAR,
		TOKEN_EQUALS,
		BAD_TOKEN,
		TOKEN_EOF,
	}	e_type;
	char	*value;
	size_t	number_of_tokens;
	int		f_space;
}		t_token;

t_token		*init_token(int type, char *value, int f_space);
void		destroy_token(t_token *token);
char		*print_token_type(int type);

#endif /* ifndef TOKEN_H */
