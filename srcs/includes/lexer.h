#ifndef LEXER_H
# define LEXER_H

# include <unistd.h>
# include <stdio.h>
# include "../../libs/libft/srcs/libft.h"
# include "token.h"

# define SPECIAL "\"'$\\;|><"
# define SPACE ' '

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
char		*lexer_chtostr(char c);
t_token		*lexer_collect_id(t_lexer *lexer);
t_token		*lexer_advance_with(t_lexer *lexer, t_token *token);
t_token		*lexer_collect_dquote(t_lexer *lexer);
t_token		*lexer_collect_dollar(t_lexer *lexer);
char		lexer_peek(t_lexer *lexer, int offset);
t_token		*lexer_collect_dgreat(t_lexer *lexer);
t_token		*lexer_collect_bslash(t_lexer *lexer);
size_t		lexer_count_quotes(char *str, char qt);
t_token		*lexer_collect_equals(t_lexer *lexer);

#endif /* ifndef LEXER_H */
