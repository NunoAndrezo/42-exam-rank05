#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct s_game
{
	char **map;
	char **new_map;

	int width;
	int height;
	int interactions;
} t_game;

void init_game(t_game *game);
void grab_args(char **av, t_game *game);
void allocate_map(t_game *game);
void create_map(t_game *game);
void free_map(t_game *game, int n);
void free_new_map(t_game *game);
void play_game_of_life(t_game *game);
void copy_new_map_to_map(t_game *game);
int count_neighbours(t_game *game, int y, int x);
void allocate_new_map(t_game *game);

int main(int ac, char **av)
{
	if (ac != 4)
		return -1;
	t_game game;
	init_game(&game);
	grab_args(av, &game);
	allocate_map(&game);
	create_map(&game);
	if (game.interactions == 0)
	{
		int y = 0;
		int x = 0;
		while (y < game.height)
		{
			x = 0;
			while(game.map[y][x])
			{
				putchar(game.map[y][x]);
				x++;
			}
			putchar('\n');
			y++;
		}
		free_map(&game, game.height);
	}
	else
	{
		play_game_of_life(&game);
		int y = 0;
		int x = 0;
		while (y < game.height)
		{
			x = 0;
			while(game.map[y][x])
			{
				putchar(game.map[y][x]);
				x++;
			}
			putchar('\n');
			y++;
		}
		free_map(&game, game.height);
	}
	return 0;
}

void play_game_of_life(t_game *game)
{
	int k = 0;
	int neighbours = 0;
	
	while (k < game->interactions)
	{
		int j = 0;
		allocate_new_map(game);
		while (j < game->height)
		{
			int i = 0;
			while(game->map[j][i])
			{
				if (game->map[j][i] == '0')
				{
					neighbours = count_neighbours(game, j, i);
					if (neighbours < 2 || neighbours > 3)
						game->new_map[j][i] = ' ';
				}
				else if (game->map[j][i] == ' ')
				{
					if (count_neighbours(game, j, i) == 3)
						game->new_map[j][i] = '0';
				}
				i++;
			}
			j++;
		}
		copy_new_map_to_map(game);
		free_new_map(game);
		k++;
	}
}

void allocate_new_map(t_game *game)
{
	game->new_map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->new_map)
		putchar('M'), exit(1);
	game->new_map[game->height] = NULL;
	for (int i = 0; i < game->height; i++)
	{
		game->new_map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->new_map[i])
		{
			free_map(game, i);
			putchar('E'), exit(1);
		}
	}
	int i = 0;
	int j = 0;
	while (j < game->height)
	{
		i = 0;
		while(i < game->width)
		{
			game->new_map[j][i] = game->map[j][i];
			i++;
		}
		game->new_map[j][i] = '\0';
		j++;
	}
}

int count_neighbours(t_game *game, int y, int x)
{
	int neighbours = 0;
	if(y - 1 >= 0)
	{
		if (game->map[y - 1][x] == '0')
			neighbours++;
	}
	if(y + 1 < game->height)
	{
		if (game->map[y + 1][x] == '0')
			neighbours++;
	}
	if (x - 1 >= 0)
	{
		if (game->map[y][x - 1] == '0')
			neighbours++;
	}
	if (x + 1 < game->width)
	{
		if (game->map[y][x + 1] == '0')
			neighbours++;
	}
	if (x + 1 < game->width && y + 1 < game->height)
	{
		if (game->map[y + 1][x + 1] == '0')
			neighbours++;
	}
	if (x - 1 >= 0 && y + 1 < game->height)
	{
		if (game->map[y + 1][x - 1] == '0')
			neighbours++;
	}
	if (x - 1 >= 0 && y - 1 >= 0)
	{
		if (game->map[y - 1][x - 1] == '0')
			neighbours++;
	}
	if (x + 1 < game->width && y - 1 >= 0)
	{
		if (game->map[y - 1][x + 1] == '0')
			neighbours++;
	}
	return neighbours;
}

void copy_new_map_to_map(t_game *game)
{
	int y = 0;
	int x = 0;
	while (y < game->height)
	{
		x = 0;
		while (game->new_map[y][x])
		{
			game->map[y][x] = game->new_map[y][x];
			x++;
		}
		y++;
	}
}

void free_new_map(t_game *game)
{
	if (game->new_map)
	{
		for(int i = 0; i < game->height; i++)
		{
			free(game->new_map[i]);
			game->new_map[i] = NULL;
		}
		free(game->new_map);
	}
}

void free_map(t_game *game, int n)
{
	if (game->map)
	{
		for(int i = 0; i < n; i++)
		{
			free(game->map[i]);
			game->map[i] = NULL;
		}
		free(game->map);
	}
}

void init_game(t_game *game)
{
	game->height = 0;
	game->interactions = 0;
	game->width = 0;
	game->map = NULL;
	game->new_map = NULL;
}

void grab_args(char **av, t_game *game)
{
	game->width = atoi(av[1]);
	game->height = atoi(av[2]);
	game->interactions = atoi(av[3]);

	if (game->width <= 0 || game->height <=0 || game->interactions < 0)
		putchar('E'), exit(1);
}

void allocate_map(t_game *game)
{
	game->map = (char **)malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		putchar('M'), exit(1);
	game->map[game->height] = NULL;
	for (int i = 0; i < game->height; i++)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (game->width + 1));
		if (!game->map[i])
		{
			free_map(game, i);
			putchar('E'), exit(1);
		}
	}
	int i = 0;
	int j = 0;
	while (j < game->height)
	{
		i = 0;
		while(i < game->width)
		{
			game->map[j][i] = ' ';
			i++;
		}
		game->map[j][i] = '\0';
		j++;
	}
}

void create_map(t_game *game)
{
	char buf;
	int x = 0;
	int y = 0;
	bool pen_down = false;

	while(read(STDIN_FILENO, &buf, 1) > 0)
	{
		if (buf == 'w')
		{
			if(y - 1 >= 0)
				y--;
		}
		else if (buf == 's')
		{
			if(y + 1 < game->height)
				y++;
		}
		else if (buf == 'a')
		{
			if (x - 1 >= 0)
				x--;
		}
		else if (buf == 'd')
		{
			if (x + 1 < game->width)
				x++;
		}
		else if (buf == 'x')
		{
			pen_down = !pen_down;
		}
		if (pen_down == true && x >= 0 && x < game->width && y >= 0 && y < game->height)
			game->map[y][x] = '0';
	}
}