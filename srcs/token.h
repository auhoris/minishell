#ifndef TOKEN_H
# define TOKEN_H

# include "../libs/libft/srcs/libft.h"

typedef struct s_token
{
	enum
	{
		TOKEN_ID, //0
		TOKEN_BSLASH, //1
		TOKEN_STRING, //2
		TOKEN_SEMICOLON, //3
		TOKEN_LESS, //4
		TOKEN_MORE, //5
		TOKEN_DMORE, //6
		TOKEN_PIPE, //7
		TOKEN_DOLLAR, //8
		TOKEN_NULL, //9
		TOKEN_EOF //10
	}	e_type;
	char	*value;
}		t_token;

t_token		*init_token(int type, char *value);

#endif /* ifndef TOKEN_H */
