#ifndef TYPES_H
# define TYPES_H

# define ARROW_UP "\e[A"
# define ARROW_DOWN "\e[B"

typedef struct	s_history
{
	char				*command;
	struct s_history	*next;
	struct s_history	*prev;

}				t_history;


#endif