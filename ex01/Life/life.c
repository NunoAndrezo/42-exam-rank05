#include "life.h"

int	main(int ac, char **av)
{
	if (ac != 4)
		return 1;
	t_game game;
	init_game(&game);
	if (grab_args(av, &game))
		return 1;
	if (make_the_map(&game))
		return 1;
	if (parse_steps(&game))
		return 1;
	if (game.iterations == 0)
		print_map(&game);
 	else
		play_game_of_life(&game);
	int	i = 0;
	while (i < game.height)
	{
		free(game.map[i]);
		i++;
	}
	free(game.map);
	if (game.is_new_map == true)
	{
			i = 0;
			while (i < game.height)
		{
			free(game.new_map[i]);
			i++;
		}
		free(game.new_map);
	}
	return 0;
}

void init_game(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->iterations = 0;
	game->map = NULL;
	game->new_map = NULL;
	game->is_new_map = false;
}

int grab_args(char **av, t_game *game)
{
	game->width = atoi(av[1]);
	game->height = atoi(av[2]);
	game->iterations = atoi(av[3]);
	if (game->width <= 0 || game->height <= 0 || game->iterations < 0)
		return 1;
	return 0;
}

int make_the_map(t_game *game)
{
	game->map = (char **)malloc((game->height + 1) * sizeof(char *));
	if (!game->map)
		return 1;
	game->map[game->height] = NULL;

	int i = 0;
	int j;
	while(i < game->height)
	{
		game->map[i] = (char *)malloc((game->width + 1) * sizeof(char));
		if (!game->map[i])
			return 1;

		j = 0;
		while (j < game->width)
		{
			game->map[i][j] = ' ';
			j++;
		}
		game->map[i][j] = '\0';
		i++;
	}
	return 0;
}

int parse_steps(t_game *game)
{
	char buf;
	bool pen_down = false;
	int	i = 0;
	int j = 0;
	int cur_pos_x = 0;
	int cur_pos_y = 0;

	while (read(STDIN_FILENO, &buf, 1) > 0)
	{
			if (buf == 'x')
				pen_down = !pen_down;
			else if (buf == 'w')
			{
				if (cur_pos_y > 0)
					cur_pos_y -= 1;
			}
			else if (buf == 's')
			{
				if (cur_pos_y < game->height -1)
					cur_pos_y += 1;
			}
			else if (buf == 'a')
			{
				if (cur_pos_x > 0)
					cur_pos_x -= 1;
			}
			else if (buf == 'd')
			{
				if (cur_pos_x < game->width -1)
					cur_pos_x += 1;
			}
			if (pen_down == true && cur_pos_x >= 0 && cur_pos_x < game->width && cur_pos_y >=0 && cur_pos_y < game->height)
				game->map[cur_pos_y][cur_pos_x] = '0';
	}
	return 0;
}

void print_map(t_game *game)
{
	int	i;

	i = 0;
	while(i < game->height)
	{
		printf("%s\n", game->map[i]);
		i++;
	}
}

void play_game_of_life(t_game *game)
{
	/* 
		Alive Cell:
			to stay alive, need to have 2 or 3 neighboors
		else
			dies

		Dead cell:
			if has 3 (exact) alive cells next - born

		outside of map counts has dead cells.
	*/
	int	k = 0;
	int	i;
	int	j = 0;
	int	cells_alive = 0;
	game->is_new_map = true;
	make_the_new_map(game);
	while (k < game->iterations)
	{
		j = 0;
		//printf("@@ game iterations:%d @@, k value: %d\n", game->iterations, k);
		while (j < game->height)
		{
			i = 0;
			while (game->map[j][i])
			{
				cells_alive = count_neighboors(game, j, i);
				if (cells_alive == 3 && game->map[j][i] == ' ')
				{
					game->new_map[j][i] = '0';
				}
				else if (cells_alive >= 2 && cells_alive <= 3 && game->map[j][i] == '0')
				{
					game->new_map[j][i] = '0';
				}
				else if ((cells_alive < 2 || cells_alive > 3) && game->map[j][i] == '0')
				{
					game->new_map[j][i] = ' ';
				}
				i++;
			}
			cells_alive = 0;
			j++;
		}
		copy_new_map_to_map(game);
		int u = 0;
		while (u < game->height)
		{
			free(game->new_map[u]);
			game->new_map[u] = NULL;
			u++;
		}
		free(game->new_map);
		game->new_map = NULL;
		make_the_new_map(game);
		k++;
	}
	print_map(game);
}

void copy_new_map_to_map(t_game *game)
{
	int	i = 0;
	int j = 0;

	while (j < game->height)
	{
		i = 0;
		while (game->new_map[j][i])
		{
			game->map[j][i] = game->new_map[j][i];
			i++;
		}
		j++;
	}
}

int	count_neighboors(t_game *game, int y, int x)
{
	int alive_cells = 0;
	
	if (y - 1 >= 0)
	{
		if (game->map[y -1][x] == '0')
			alive_cells++;
	}

	if (y + 1 < game->height)
	{
		if (game->map[y +1][x] == '0')
			alive_cells++;
	}

	if (x - 1 >= 0)
	{
		if (game->map[y][x - 1] == '0')
			alive_cells++;
	}

	if (x + 1 < game->width)
	{
		if (game->map[y][x + 1] == '0')
			alive_cells++;
	}

	if (x - 1 >= 0 && y - 1 >= 0)
	{
		if (game->map[y -1][x - 1] == '0')
			alive_cells++;
	}

	if (x - 1 >= 0 && y + 1 < game->height)
	{
		if (game->map[y + 1][x - 1] == '0')
			alive_cells++;
	}

	if (x + 1 < game->width && y - 1 >= 0)
	{
		if (game->map[y - 1][x + 1] == '0')
			alive_cells++;
	}

	if (x + 1 < game->width && y + 1 < game->height)
	{
		if (game->map[y + 1][x + 1] == '0')
			alive_cells++;
	}
	//printf("cells that are alive:%d, at pos(%d, %d)\n", alive_cells, x, y);
	return alive_cells;
}

int make_the_new_map(t_game *game)
{
	game->new_map = (char **)malloc((game->height + 1) * sizeof(char *));
	if (!game->new_map)
		return 1;
	game->new_map[game->height] = NULL;

	int i = 0;
	int j;
	while(i < game->height)
	{
		game->new_map[i] = (char *)malloc((game->width + 1) * sizeof(char));
		if (!game->new_map[i])
			return 1;

		j = 0;
		while (j < game->width)
		{
			game->new_map[i][j] = ' ';
			j++;
		}
		game->new_map[i][j] = '\0';
		i++;
	}
	return 0;
}