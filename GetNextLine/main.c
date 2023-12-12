#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include "get_next_line.h" 
#include <stdio.h> 

int	get_next_line(const int fd, char **line);

void	ft_strdel2(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}

int	main(int ac, char **av)
{
	char *line;
	int fd;
	int ret;
	int i;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%s\n", line);
			ft_strdel2(&line);
		}	
		close(fd);
	}
	i = 0;
	return (0);
}
