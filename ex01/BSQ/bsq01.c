#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_bsq
{
	int biggest;
	int x_start;
	int y_start;

	int str_len;

	int n_lines;
	char empty;
	char obstacle;
	char full;

	char **map;
} t_bsq;

int execute_bsq(t_bsq *bsq);
void print_map(t_bsq *bsq);
void find_biggest(int val, int y, int x, t_bsq *bsq);
int find_min(int a, int b, int c);
int get_data(t_bsq *bsq, FILE *file);
int allocate_map(t_bsq *bsq, char *line);
void free_map(t_bsq *bsq, int n);
int ft_strlen(char *s);
int grab_map_info(t_bsq *bsq, char *line);
void init_bsq(t_bsq *bsq);

int main(int ac, char **av)
{
	t_bsq bsq;

	init_bsq(&bsq);
	if (ac == 1)
	{
		if (get_data(&bsq, stdin))
			return -1;
		if (execute_bsq(&bsq))
			return -1;
		free_map(&bsq, bsq.n_lines);
	}
	else if (ac == 2)
	{
		FILE *file = fopen(av[1], "r");
		if(!file)
			return printf("Error: fopen\n"), -1;
		if (get_data(&bsq, file))
			return fclose(file), -1;
		if (execute_bsq(&bsq))
			return fclose(file), -1;
		free_map(&bsq, bsq.n_lines);
		fclose(file);
	}
	else
	{
		printf("Error: bla\n");
		return -1;
	}
	return 0;
}

int execute_bsq(t_bsq *bsq)
{
	int y = 0;
	int x = 0;
	int matrix[bsq->n_lines][bsq->str_len];

	while(y < bsq->n_lines)
	{
		x = 0;
		while(bsq->map[y][x] && bsq->map[y][x] != '\n')
		{
			if(bsq->map[y][x] == bsq->obstacle)
				matrix[y][x] = 0;
			else if (x == 0 || y == 0)
				matrix[y][x] = 1;
			else
				matrix[y][x] = find_min(matrix[y -1][x], matrix[y-1][x-1], matrix[y][x-1]) + 1;
			find_biggest(matrix[y][x], y, x, bsq);
			x++;
		}
		y++;
	}

// xxx.
// xxx.
// xxx.
// ....
	
	y = bsq->y_start;
	int sqr_y = bsq->biggest;
	int sqr_x = bsq->biggest;
	while(sqr_y > 0)
	{
		sqr_x = bsq->biggest;
		x = bsq->x_start;
		while(sqr_x > 0)
		{
			bsq->map[y][x] = bsq->full;
			x--;
			sqr_x--;
		}
		y--;
		sqr_y--;
	}
	print_map(bsq);
	return 0;
}

void print_map(t_bsq *bsq)
{
	int y = 0;

	while(y < bsq->n_lines)
	{
		printf("%s\n", bsq->map[y]);
		y++;
	}
}

void find_biggest(int val, int y, int x, t_bsq *bsq)
{
	if (val > bsq->biggest)
	{
		bsq->biggest = val;
		bsq->x_start = x;
		bsq->y_start = y;
	}
}

int find_min(int a, int b, int c)
{
	int min = a;

	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return min;
}

int get_data(t_bsq *bsq, FILE *file)
{
	char *line = NULL;
	size_t n = 0;

	if (getline(&line, &n, file) < 0)
		return printf("Error: getline\n"), -1;
	if (grab_map_info(bsq, line))
	{
		n = 0;
		free(line);
		line = NULL;
		return printf("Error: grab_map_info\n"), -1;
	}
	n = 0;
	free(line);
	line = NULL;
	if (getline(&line, &n, file) < 0)
		return printf("Error: getline\n"), -1;
	bsq->str_len = ft_strlen(line);
	if (allocate_map(bsq, line))
	{
		n = 0;
		free(line);
		line = NULL;
		return printf("Error: allocate_map\n"), -1;
	}
	n = 0;
	free(line);
	line = NULL;
	int x = 0;
	int y = 1;

	while (getline(&line, &n, file) != -1)
	{
		x = 0;
		while(line[x] && line[x] != '\n')
		{
			bsq->map[y][x] = line[x];
			x++;
		}
		bsq->map[y][x] = '\0';
		if (ft_strlen(bsq->map[y]) != bsq->str_len)
		{
			n = 0;
			free(line);
			line = NULL;
			free_map(bsq, bsq->n_lines);
			printf("Error: len not equal in all strings\n");
			return -1;
		}
		y++;
		n = 0;
		free(line);
		line = NULL;
	}
	n = 0;
	free(line);
	line = NULL;
	return 0;
}

int allocate_map(t_bsq *bsq, char *line)
{
	bsq->map = (char **)malloc(sizeof(char *) *(bsq->n_lines + 1));
	if(!bsq->map)
		return -1;
	bsq->map[bsq->n_lines] = NULL;
	int i = 0;
	while (i < bsq->n_lines)
	{
		bsq->map[i] = (char *)malloc(sizeof(char) * (bsq->str_len + 1));
		if (!bsq->map[i])
		{
			free_map(bsq, i);
			return -1;
		}
		i++;
	}

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		bsq->map[0][i] = line[i];
		i++;
	}
	bsq->map[0][i] = '\0';
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

int ft_strlen(char *s)
{
	int i = 0;
	if (!s)
		return i;
	while (s[i] && s[i] != '\n')
		i++;
	return i;
}

int grab_map_info(t_bsq *bsq, char *line)
{
	int i = 0;
	while(line[i] == ' ')
		i++;
	while(line[i] >= '0' && line[i] <= '9')
	{
		bsq->n_lines *= 10;
		bsq->n_lines += line[i] - 48;
		i++;
	}
	while(line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->empty = line[i];
		i++;
	}
	while(line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->obstacle = line[i];
		i++;
	}
	while(line[i] == ' ')
		i++;
	if (line[i] >= 33 && line[i] <= 126)
	{
		bsq->full = line[i];
		i++;
	}

	if (bsq->n_lines <= 0 || !bsq->empty || !bsq->obstacle || !bsq->full)
		return -1;
	return 0;
}

void init_bsq(t_bsq *bsq)
{
	bsq->map = NULL;
	bsq->n_lines = 0;
	bsq->empty = '\0';
	bsq->obstacle = '\0';
	bsq->full = '\0';

	bsq->str_len = 0;

	bsq->x_start = 0;
	bsq->y_start = 0;
	bsq->biggest = 0;
}