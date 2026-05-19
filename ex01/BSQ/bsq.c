#include "bsq.h"

static int execute_bsq(FILE *file, t_bsq *bsq);
static void init_bsq(t_bsq *bsq);
static int get_map(FILE *file, t_bsq *bsq);
static int get_data(FILE *file, t_bsq *bsq);
void free_map(t_bsq *bsq, int n);
static void find_biggest(t_bsq *bsq, int matrix_val, int y, int x);
static int find_min(int a, int b, int c);
static int ft_strlen(char *s);
static int allocate_map(t_bsq *bsq);
void print_map(t_bsq *bsq);

int	main(int ac, char *av[])
{
	t_bsq bsq;

	init_bsq(&bsq);
	if (ac == 1)
	{
		if (execute_bsq(stdin, &bsq))
			return (fprintf(stderr, "map error\n"), 1);
		print_map(&bsq);
		free_map(&bsq, bsq.n_lines);
	}
	else if (ac == 2)
	{
		FILE *file;
		if ((file = fopen(av[1], "r")) == NULL)
			return (fprintf(stderr, "map error\n"), 1);
		if (execute_bsq(file, &bsq))
			return (fclose(file), fprintf(stderr, "map error\n"), 1);
		print_map(&bsq);
		fclose(file);
		free_map(&bsq, bsq.n_lines);
	}
	else
		return (fprintf(stderr, "map error\n"), 1);
	return (0);
}

void print_map(t_bsq *bsq)
{
	int y = 0;
	while (y < bsq->n_lines)
	{
		printf("%s\n", bsq->map[y]);
		y++;
	}
}

static void init_bsq(t_bsq *bsq)
{

	bsq->map = NULL;
	bsq->array_size = 0;

	bsq->n_lines = 0;
	bsq->obstacle = '\0';
	bsq->full = '\0';
	bsq->empty = '\0';

	bsq->sqr_size = 0;
	bsq->x_start = 0;
	bsq->y_start = 0;
}

static int execute_bsq(FILE *file, t_bsq *bsq)
{
	if (get_map(file, bsq))
		return -1;
	int height = bsq->n_lines;
	int width = bsq->array_size;
	int matrix[height][width];
	int x = 0;
	int y = 0;

	while (y < height)
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
			find_biggest(bsq, matrix[y][x], y, x);
			x++;
		}
		y++;
	}

	int sqr_x = bsq->sqr_size;
	int sqr_y = bsq->sqr_size;

	y = bsq->y_start;
	x = bsq->x_start;
	while (sqr_y > 0)
	{
		sqr_x = bsq->sqr_size;
		x = bsq->x_start;
		while (sqr_x > 0)
		{
			bsq->map[y][x] = bsq->full;
			sqr_x--;
			x--;
		}
		y--;
		sqr_y--;
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

static void find_biggest(t_bsq *bsq, int matrix_val, int y, int x)
{
	if (matrix_val > bsq->sqr_size)
	{
		bsq->sqr_size = matrix_val;
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

	int	i = 0;

	bool	have_array_size = false;

	while (getline(&line, &n, file) > 0)
	{
		if (have_array_size == false)
		{
			bsq->array_size = ft_strlen(line);
			have_array_size = true;
		}
		if (bsq->array_size != ft_strlen(line))
		{
			free_map(bsq, i);
			free(line);
			return -1;
		}
		bsq->map[i] = (char *)malloc(sizeof(char) * (bsq->array_size + 1));
		if (!bsq->map[i])
		{
			free_map(bsq, i);
			free(line);
			return -1;
		}
		int j = 0;
		while (line[j] && line[j] != '\n')
		{
			bsq->map[i][j] = line[j];
			j++;
		}
		bsq->map[i][j] = '\0';
		free(line);
		line = NULL;
		n = 0;
		i++;
	}
	free(line);
	return 0;
}

static int ft_strlen(char *s)
{
	int i = 0;

	if (!s)
		return 0;
	while (s[i] && s[i] != '\n')
		i++;
	return i;
}

static int get_data(FILE *file, t_bsq *bsq)
{
	char *line = NULL;
	size_t n = 0;
	int i = 0;

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
		return free(line), -1;
	free(line);
	line = NULL;
	if (bsq->n_lines <= 0 || !bsq->empty || !bsq->obstacle || !bsq->full)
		return -1;
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