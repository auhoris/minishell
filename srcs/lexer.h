#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdio.h>
# include "../libs/libft/srcs/libft.h"
# include "token.h"

typedef struct s_lexer
{
	char	*content;
	char	c;
	size_t	current;
	size_t	length;
}				t_lexer;

t_lexer		*init_lexer(char *content);
void		lexer_advance(t_lexer *lexer);
t_token		*lexer_get_next_token(t_lexer *lexer);
void		lexer_skip_whitespace(t_lexer *lexer);
t_token		*lexer_collect_squote(t_lexer *lexer);
char		*lexer_get_char_as_str(char c);
t_token		*lexer_collect_id(t_lexer *lexer);
t_token		*lexer_advance_with_token(t_lexer *lexer, int type);
t_token		*lexer_collect_dquote(t_lexer *lexer);
t_token		*lexer_collect_dollar(t_lexer *lexer);

#endif /* ifndef LEXER_H */
