#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Visualize the utility of strerror()
 * 
 * @return int
 */
int	main(void)
{
	int		errno;
	char	*error_message;

	for (errno = 0; errno < 259; errno++) // Note: 255 is not the max value. See how it does not crash with those values.
	{
		error_message = strerror(errno);
		printf("%d. %s\n", errno, error_message);
	}
	return (0);
}