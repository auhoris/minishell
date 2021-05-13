#include "includes/lexer.h"
#include "includes/minishell.h"

char	*lexer_chtostr(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(*str));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	lexer_advance(t_lexer *lexer)
{
	lexer->current++;
	lexer->c = lexer->content[lexer->current];
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ')
		lexer_advance(lexer);
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

char	lexer_peek(t_lexer *lexer, int offset)
{
	if (lexer->current + offset < lexer->length)
		return (lexer->content[lexer->current + offset]);
	return (lexer->content[lexer->length - 1]);
}

char	*connect_str(char *s1, char *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	free(tmp);
	if (s1 == NULL)
		return (NULL);
	return (s1);
}

int	check_command(char *value)
{
	char	*commands[10];
	size_t	i;

	commands[0] = "echo ";
	commands[1] = "cd ";
	commands[2] = "pwd ";
	commands[3] = "export ";
	commands[4] = "unset ";
	commands[5] = "env ";
	commands[6] = "exit ";
	commands[7] = NULL;
	i = 0;
	while (commands[i])
	{
		if (!ft_strncmp(value, commands[i], ft_strlen(value)))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
