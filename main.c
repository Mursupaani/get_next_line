#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;

	fd = open("testing.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("File not found\n");
		return (0);
	}
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line)
			printf("%s", line);
	}
	free(line);
	close(fd);
	return (0);
}
