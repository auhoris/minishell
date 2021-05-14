#ifndef TOKEN_H
# define TOKEN_H

# include "../../libs/libft/srcs/libft.h"

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
		TOKEN_LESS, //6
		TOKEN_MORE, //7
		TOKEN_DMORE, //8
		TOKEN_PIPE, //9
		TOKEN_DOLLAR, //10
		TOKEN_EQUALS, //11
		BAD_TOKEN, //12
		TOKEN_EOF, //13
	}	e_type;
	char	*value;
}		t_token;

t_token		*init_token(int type, char *value);

#endif /* ifndef TOKEN_H */
