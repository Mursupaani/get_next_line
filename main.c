#include "get_next_line.h"
#include <stdio.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("File not found\n");
		return (0);
	}
	line = get_next_line(fd);
	printf("%s", line);
	if (!line)
		return (0);
	while (line && *line)
	{
		line = get_next_line(fd);
		if (line)
			printf("%s", line);
	}
		printf("\n");
	close(fd);
	return (0);
}
