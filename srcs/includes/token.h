#ifndef TOKEN_H
# define TOKEN_H

# include "../../libs/libft/srcs/libft.h"

typedef struct s_token
{
	enum
	{
		TOKEN_ID, //0
		TOKEN_BSLASH, //1
		TOKEN_SQUOTE, //2
		TOKEN_DQUOTE, //3
		TOKEN_SEMI, //4
		TOKEN_LESS, //5
		TOKEN_MORE, //6
		TOKEN_DMORE, //7
		TOKEN_PIPE, //8
		TOKEN_DOLLAR, //9
		BAD_TOKEN, //10
		TOKEN_EOF, //11
		TOKEN_EQUALS, //12
	}	e_type;
	char	*value;
}		t_token;

t_token		*init_token(int type, char *value);

#endif /* ifndef TOKEN_H */
