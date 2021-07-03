#include "libft.h"

int	ft_noprint(int c)
{
	if (c >= 0 && c <= 31)
		return (1);
	return (0);
}
