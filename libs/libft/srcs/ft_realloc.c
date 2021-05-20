#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t newsize, size_t oldsize)
{
	void	*ptr_new;

	if (newsize == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (ptr == NULL)
	{
		return (malloc(newsize));
	}
	else if (newsize <= oldsize)
		return (ptr);
	else
	{
		ptr_new = malloc(newsize);
		if (ptr_new)
		{
			ft_memcpy(ptr_new, ptr, oldsize);
			free(ptr);
		}
		return (ptr_new);
	}
	return (ptr_new);
}
