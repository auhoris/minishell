#ifndef UTILS_H
# define UTILS_H

# include "lexer.h"

char	*connect_str(char *s1, char *s2);
int		check_command(char *value);
void	handle_error_msg(char *msg, char *token);

#endif /* ifndef UTILS_H */
