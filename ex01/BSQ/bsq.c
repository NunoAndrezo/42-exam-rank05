#include "bsq.h"

static int execute_bsq(FILE *file, t_bsq *bsq);
static void init_bsq(t_bsq *bsq);

/* 
FILE *file = fopen(path, "r");

int matrix[height][width];

min = (matrix[y - 1][x], matrix[y][x - 1], matrix[y - 1][x - 1]) + 1
find_min()

find_biggest();
 */

int	main(int ac, char *av[])
{
	t_bsq bsq;

	init_bsq(&bsq);
	if (ac == 1)
	{
		if (execute_bsq(stdin, &bsq))
			return (fprintf(stderr, "map error\n"), 1);
	}
	else if (ac == 2)
	{
		FILE *file;
		if ((file = fopen(av[1], "r")) == NULL)
			return (fprintf(stderr, "map error\n"), 1);
		if (execute_bsq(file, &bsq))
			return (fprintf(stderr, "map error\n"), 1);
		fclose(file);
	}
	else
		return (fprintf(stderr, "map error\n"), 1);
	return (0);
}

static void init_bsq(t_bsq *bsq)
{
	bsq->n_lines = 0;

	bsq->map = NULL;

	bsq->x_start = 0;
	bsq->y_start = 0;
	bsq->biggest = 0;
}

static int execute_bsq(FILE *file, t_bsq *bsq)
{

}
