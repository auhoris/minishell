#ifndef TOKEN_H
# define TOKEN_H

# include "../../libs/libft/srcs/libft.h"
#include <sys/_types/_size_t.h>

typedef struct s_token
{
	enum
	{
		TOKEN_ID, //0
		TOKEN_CMD, //1
		TOKEN_BSLASH, //2
		TOKEN_SQUOTE, //3
		TOKEN_DQUOTE, //4
		TOKEN_SEMI, //5
		TOKEN_LESS, //6 Работает как редирект при записи: >echo
		TOKEN_MORE, //7 То же что и выше
		TOKEN_DMORE, //8 То же что и выше
		TOKEN_PIPE, //9
		TOKEN_DOLLAR, //10 При записи: $echo (и т.п.) value токена воспринимается как переменная окружения
		TOKEN_EQUALS, //11
		TOKEN_FLAG, //12
		BAD_TOKEN, //13
		TOKEN_EOF, //14
	}	e_type;
	char	*value;
	size_t	number_of_tokens;
}		t_token;

t_token		*init_token(int type, char *value);
void		destroy_token(t_token *token);

#endif /* ifndef TOKEN_H */
