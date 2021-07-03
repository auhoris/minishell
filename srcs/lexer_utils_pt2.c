#include "includes/errors.h"
#include "includes/lexer.h"
#include "includes/minishell.h"
#include <stdlib.h>
#include <sys/_types/_size_t.h>

int	seek_quote(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && str[i - 1] != '\\')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*connect_str(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	if (s1 == NULL)
		return (NULL);
	free(s2);
	s2 = NULL;
	return (s1);
}

void	handle_error_msg(char *msg, char *token)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (ft_strcmp(token, "") == 0)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	if (g_data_processing->n_state == FALSE)
		ft_putchar_fd('\n', STDERR_FILENO);
}
