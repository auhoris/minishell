#include "libft.h"

int	ft_putint(int c)
{
	write(1, &c, 1);
	return (1);
}