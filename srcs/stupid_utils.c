#include <stdio.h>

void	cout_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("[%d]\t%s\n", i, arr[i]);
		i++;
	}
}

