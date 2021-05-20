#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (NULL);
	free(ptr);
	ptr = ft_calloc(1, size);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}