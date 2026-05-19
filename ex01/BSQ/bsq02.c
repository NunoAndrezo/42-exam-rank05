#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_bsq
{
	int biggest;
	int x_start;
	int y_start;

	char **map;

	int nr_lines;
	char empty;
	char obstacle;
	char full;
} t_bsq;

int main(int ac, char **av)
{
	t_bsq bsq;

	init_bsq(&bsq);
	if (ac == 1)
	{
		if (execute_bsq(stdin, &bsq))
			return -1;
	}
	else if (ac == 2)
	{
		FILE *file = fopen(av[1], "r");
		if (!file)
			return fprintf(stderr, "Error: fopen\n"), -1;
		if (execute_bsq(file, &bsq))
			return fclose(file), -1;
		fclose(file);
	}
	return 0;
}

void free_map(t_bsq *bsq, int n)
{
	if (bsq->map)
	{
		for(int i = 0; i < n; i++)
		{
			free(bsq->map[i]);
		}
		free(bsq->map);
	}
}

void init_bsq(t_bsq *bsq)
{
	bsq->nr_lines = 0;
	bsq->empty = '\0';
	bsq->full = '\0';
	bsq->obstacle = '\0';

	bsq->map = NULL;

	bsq->biggest = 0;
	bsq->x_start = 0;
	bsq->y_start = 0;
}

int execute_bsq(FILE *file, t_bsq *bsq)
{
	char *line = NULL;
	size_t n = 0;
	if (getline(&line, &n, file) == -1)
	{
		if(line)
		{
			free(line);
			line = NULL;
		}
		return fprintf(stderr, "Error: getline\n"), -1;
	}
	if (grab_data(bsq, line))
		return -1;
	return 0;
}

int grab_data(t_bsq *bsq, char *line)
{
	
}

