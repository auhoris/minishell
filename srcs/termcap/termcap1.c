#include <term.h>
#include <errno.h>
#include <string.h>
#include "../includes/types.h"
#include "../../libs/libft/srcs/libft.h"

int	get_term_param(struct termios *term, struct termios *term_default)
{
	char	*term_name;
	int		out;

	term_name = getenv("TERM");
	if (term_name == NULL)
		return (ERROR_TERM_NAME);
	out = tcgetattr(0, term);
	tcgetattr(0, term_default);
	if (out != 0)
	{
		ft_putstr(strerror(errno));
		return (ERROR);
	}
	term->c_lflag &= ~(ECHO);
	term->c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, term);
	out = tgetent(0, term_name);
	if (out == 0)
		return (ERROR);
	else if (out == -1)
		return (ERROR);
	return (OUT);
}

void	screen_clear(void)
{
	tputs(tgetstr("rc", 0), 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
}
