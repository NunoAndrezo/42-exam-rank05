#include "bsq.h"


/* 
FILE *file = fopen(path, "r");

int matrix[height][width];

min = (matrix[y - 1][x], matrix[y][x - 1], matrix[y - 1][x - 1]) + 1
find_min()

find_biggest();
 */

static int execute_bsq(FILE *file, t_bsq *bsq);
static void init_bsq(t_bsq *bsq);
static int get_map(FILE *file, t_bsq *bsq);
static int get_data(FILE *file, t_bsq *bsq);

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
	bsq->array_size = 0;

	bsq->x_start = 0;
	bsq->y_start = 0;
	bsq->biggest = 0;
}

static int execute_bsq(FILE *file, t_bsq *bsq)
{
	if (get_map(file, bsq))
		return -1;
	size_t height = bsq->n_lines;
	size_t width = bsq->array_size;
	int matrix[height][width];
	size_t x = 0;
	size_t y = 0;

	while (bsq->map[y] != NULL)
	{
		x = 0;
		while (bsq->map[y][x])
		{
			if (bsq->map[y][x] == bsq->obstacle)
				matrix[y][x] = 0;
			else if (x == 0 || y == 0)
				matrix[y][x] = 1;
			else
				matrix[y][x] = find_min(matrix[y - 1][x], matrix[y][x - 1], matrix[y - 1][x - 1]) + 1;
			x++;
			bsq->biggest = find_biggest(bsq, matrix[y][x], y, x);
		}
		y++;
	}
	return 0;
}

static int find_biggest(t_bsq *bsq, int matrix_val, int y, int x)
{
	
}

static int find_min(int a, int b, int c)
{
	int min = 9999;
	if (a < b)
		min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}


static int get_map(FILE *file, t_bsq *bsq)
{
	if (get_data(file, bsq))
		return -1;
	if (allocate_map(bsq))
		return -1;
	char *line = NULL;
	size_t	n = 0;
	size_t	i = 0;
	bool	have_array_size = false;
	while (1)
	{
		if (getline(&line, &n, file) > 0)
		{
			if (have_array_size == false)
			{
				bsq->array_size = ft_strlen(line);
				have_array_size = true;
			}
			if (bsq->array_size != ft_strlen(line))
			{
				free(line);
				return -1;
			}
			bsq->map[i] = (char *)malloc(sizeof(char) * (bsq->array_size + 1));
			if (!bsq->map[i])
			{
				free(line);
				return -1;
			}
			bsq->map[i][bsq->array_size] = '\0';
			size_t j = 0;
			while (line[j])
			{
				bsq->map[i][j] = line[j];
				j++;
			}
			free(line);
			line = NULL;
			i++;
		}
		else
		{
			if (line)
				free(line);
			return 0;
		}
	}
	return 0;
}

static size_t ft_strlen(char *s)
{
	size_t i = 0;

	if (!s)
		return -1;
	while (s[i])
		i++;
	return i;
}

static int get_data(FILE *file, t_bsq *bsq)
{
	char *line = NULL;
	size_t n = 0;
	size_t i = 0;

	if (getline(&line, &n, file) < 0)
		return -1;
	while (line[i] == ' ')
		i++;
	if (!(line[i] >= '0' && line[i] <= '9'))
		return -1;
	while (line[i] >= '0' && line[i] <= '9')
	{
		bsq->n_lines *= 10;
		bsq->n_lines += line[i] - 48;
		i++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->empty = line[i];
		i++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->obstacle = line[i];
		i++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->full = line[i];
		i++;
	}
	if (line[i] != '\n' && line[i] != '\0')
		return -1;
	free(line);
	return 0;
}

static int allocate_map(t_bsq *bsq)
{
	bsq->map = (char **)malloc(sizeof(char *) * (bsq->n_lines + 1));
	if (!bsq->map)
		return -1;
	bsq->map[bsq->n_lines] = NULL;
	return 0;
}