#include "bsq.h"

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		if (execute_from_stdin(stdin))
			return (fprintf(stderr, "map error\n"), 1);
	}
	else if (ac == 2)
	{
		
	}
	else
		return (fprintf(stderr, "map error\n"), 1);
	return (0);
}
