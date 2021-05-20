#include "libft.h"
#include <sys/_types/_size_t.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	max_length;

	max_length = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
		max_length = ft_strlen(s1);
	else
		max_length = ft_strlen(s2);
	return (ft_memcmp(s1, s2, max_length));
}
