#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int		fd;
	char	*line;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
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
		printf("%s", line);
	}
		printf("\n");
	close(fd);
	return (0);
}
