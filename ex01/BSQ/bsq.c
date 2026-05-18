#include "bsq.h"


static int execute_bsq(FILE *file, t_bsq *bsq);
static void init_bsq(t_bsq *bsq);
static int get_map(FILE *file, t_bsq *bsq);
static int get_data(FILE *file, t_bsq *bsq);
static int find_min(int a, int b, int c);
static int change_map_to_bsq(t_bsq *bsq);
static void find_biggest(t_bsq *bsq, int matrix_val, int y, int x);
static size_t ft_strlen(char *s);
static int allocate_map(t_bsq *bsq);
static void free_map(t_bsq *bsq, size_t n);

int	main(int ac, char *av[])
{
	t_bsq bsq;

	init_bsq(&bsq);
	if (ac == 1)
	{
		if (execute_bsq(stdin, &bsq))
			return (fprintf(stderr, "Error: blabla\n"), 1);
		free_map(&bsq, bsq.n_lines);
	}
	else if (ac == 2)
	{
		FILE *file;
		if ((file = fopen(av[1], "r")) == NULL)
			return (fprintf(stderr, "Error: blabla\n"), fclose(file), 1);
		if (execute_bsq(file, &bsq))
			return (fprintf(stderr, "Error: blabla\n"), fclose(file), 1);
		fclose(file);
		free_map(&bsq, bsq.n_lines);
	}
	else
		return (fprintf(stderr, "Error: blabla\n"), 1);
	return (0);
}

static void free_map(t_bsq *bsq, size_t n)
{
	int i = 0;
	if (bsq->map)
	{
		while (i < n)
		{
			free(bsq->map[i]);
			bsq->map[i] = NULL;
			i++;
		}
		free(bsq->map);
	}
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

	while (y < bsq->n_lines)
	{
		x = 0;
		while (bsq->map[y][x] && bsq->map[y][x] != '\n') // ponto
		{
			if (bsq->map[y][x] == bsq->obstacle)
				matrix[y][x] = 0;
			else if (x == 0 || y == 0)
				matrix[y][x] = 1;
			else
				matrix[y][x] = find_min(matrix[y - 1][x], matrix[y][x - 1], matrix[y - 1][x - 1]) + 1;
			find_biggest(bsq, matrix[y][x], (int)y, (int)x);
			x++;
		}
		y++;
	}
	if (change_map_to_bsq(bsq))
		return -1;
	int i = 0;
	while (i < bsq->n_lines)
	{
		printf("%s", bsq->map[i]);
		i++;
	}
	return 0;
}

static int change_map_to_bsq(t_bsq *bsq) //ponto
{
// x_start and y_start represent the bottom-right corner of our biggest square
	int max_y = bsq->y_start;
	int max_x = bsq->x_start;
	int size = bsq->biggest;

	for (int y = max_y - size + 1; y <= max_y; y++)
	{
		for (int x = max_x - size + 1; x <= max_x; x++)
		{
			if (y >= 0 && y < bsq->n_lines && x >= 0 && x < (int)bsq->array_size)
			{
				bsq->map[y][x] = bsq->full;
			}
		}
	}
	return 0;
}

static void find_biggest(t_bsq *bsq, int matrix_val, int y, int x)
{
	if (matrix_val > bsq->biggest)
	{
		bsq->biggest = matrix_val;
		bsq->x_start = x;
		bsq->y_start = y;
	}
}

static int find_min(int a, int b, int c)
{
	int min = a;
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

	while (i < (size_t)bsq->n_lines)
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
				free_map(bsq, i);
				return -1;
			}
			bsq->map[i] = (char *)malloc(sizeof(char) * (bsq->array_size + 1));
			if (!bsq->map[i])
			{
				free_map(bsq, i);
				free(line);
				return -1;
			}
			size_t j = 0;
			while (line[j])
			{
				bsq->map[i][j] = line[j];
				j++;
			}
			bsq->map[i][j] = '\0';

			free(line);
			line = NULL;
			i++;
			n = 0; // ponto
		}
		else
		{
			if (line)
				free(line);
			free_map(bsq, i);
			return -1;
		}
	}
	if (line)
		free(line);
	return 0;
}

static size_t ft_strlen(char *s)
{
	size_t i = 0;

	if (!s)
		return 0;
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
		return free(line), -1;
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
		return free(line),-1;
	if (!bsq->empty || !bsq->obstacle || !bsq->full || bsq->n_lines <= 0)
		return (free(line), -1);
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