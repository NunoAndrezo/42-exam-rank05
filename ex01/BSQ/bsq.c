#include "bsq.h"

static int execute_bsq(FILE *file);
static int check_file(char *f);

int	main(int ac, char *av[])
{
	if (ac == 1)
	{
		if (execute_bsq(stdin))
			return (fprintf(stderr, "map error\n"), 1);
	}
	else if (ac == 2)
	{
		if (check_file(av[1]))
			return (fprintf(stderr, "map error\n"), 1);
	}
	else
		return (fprintf(stderr, "map error\n"), 1);
	return (0);
}

static int execute_bsq(FILE *file)
{
	char *line = NULL;
	if (getline(&line, ))
}

static int check_file(char *s)
{

}