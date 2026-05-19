#include "life01.h"

int	main(int ac, char **av)
{
	if (ac != 4)
		return -1;
	t_life life;
	init_s(&life);
	grab_args(&life, av);
	start_map(&life);
	walking(&life);
	if (life.iter == 0)
	{
		for(int i = 0; i < life.h; i++)
			printf("%s\n", life.m[i]);
		free_map(&life, life.h);
	}
	else if (life.iter > 0)
	{
		play_game(&life);
		for(int i = 0; i < life.h; i++)
			printf("%s\n", life.m[i]);
		free_map(&life, life.h);
	}
	return 0;
}

void play_game(t_life *life)
{
	int i = 0;
	int x = 0;
	int y = 0;

	/* 
	2/3 stays alive
	< 2 && > 3 - dies
	dead cell: 3 alive, born
	 */
	while (i < life->iter)
	{
		create_new_map(life);
		y = 0;
		while(y < life->h)
		{
			x = 0;
			while(life->m[y][x])
			{
				if (life->m[y][x] == '0')
				{
					if (check_neighbour(y, x, life) < 2 || check_neighbour(y, x, life) > 3)
						life->new_map[y][x] = ' ';
				}
				else if (life->m[y][x] == ' ')
				{
					if (check_neighbour(y, x, life) == 3)
						life->new_map[y][x] = '0';
				}
				x++;
			}
			y++;
		}
		cp_map(life);
		free_map_new_map(life, life->h);
		i++;
	}
}

void free_map_new_map(t_life *life, int j)
{
	if (life->new_map)
	{
		for(int i = 0; i < j; i++)
			free(life->new_map[i]);
		free(life->new_map);
	}
}

void cp_map(t_life *life)
{
	int x = 0;
	int y = 0;

	while (y < life->h)
	{
		x = 0;
		while (life->new_map[y][x])
		{
			life->m[y][x] = life->new_map[y][x];
			x++;
		}
		y++;
	}
}

int check_neighbour(int y, int x, t_life *life)
{
	int neighbour = 0;

	if (y - 1 >= 0)
	{
		if (life->m[y - 1][x] == '0')
			neighbour++;
	}
	if (x - 1 >= 0)
	{
		if (life->m[y][x - 1] == '0')
			neighbour++;
	}
	if(y + 1 < life->h)
	{
		if (life->m[y + 1][x] == '0')
			neighbour++;
	}
	if (x + 1 < life->w)
	{
		if (life->m[y][x + 1] == '0')
			neighbour++;
	}
	if (y - 1 >= 0 && x - 1 >= 0)
	{
		if (life->m[y - 1][x - 1] == '0')
			neighbour++;
	}
	if (y + 1 < life->h && x + 1 < life->w)
	{
		if (life->m[y + 1][x + 1] == '0')
			neighbour++;
	}
	if (y + 1 < life->h && x - 1 >= 0)
	{
		if (life->m[y+1][x-1] == '0')
			neighbour++;
	}
	if (y - 1 >= 0 && x + 1 < life->w)
	{
		if (life->m[y-1][x+1] == '0')
			neighbour++;
	}
	return neighbour;
}

void create_new_map(t_life *life)
{
	life->new_map = (char **)malloc(sizeof(char *) * (life->h + 1));
	if (!life->new_map)
		printf("Error\n"), exit (1); //i cant use exit in exam
	life->new_map[life->h] = NULL;

	int i = 0;
	while(i < life->h)
	{
		life->new_map[i] = (char *)malloc(sizeof(char) * (life->w + 1));
		if (!life->new_map[i])
		{
			free_map_new_map(life, i);
			printf("Error\n");
			exit(1); // cant use
		}
		i++;
	}

	int j = 0;
	while (j < life->h)
	{
		i = 0;
		while (i < life->w)
		{
			life->new_map[j][i] = life->m[j][i];
			i++;
		}
		life->new_map[j][i] = '\0';
		j++;
	}
}

void free_map(t_life *life, int j)
{
	if (life->m)
	{
		for(int i = 0; i < j; i++)
			free(life->m[i]);
		free(life->m);
	}
}

void init_s(t_life *life)
{
	life->h = 0;
	life->w = 0;
	life->iter = 0;
	life->m = NULL;
}

void grab_args(t_life *life, char **av)
{
	life->w = atoi(av[1]);
	life->h = atoi(av[2]);
	life->iter = atoi(av[3]);

	if(life->h <= 0 || life->w <=0 || life->iter < 0)
		printf("Error: grab_args"), exit(1);
}

void start_map(t_life *life)
{
	life->m = (char **)malloc(sizeof(char *) * (life->h + 1));
	if (!life->m)
		printf("Error\n"), exit (1); //i cant use exit in exam
	life->m[life->h] = NULL;

	int i = 0;
	while(i < life->h)
	{
		life->m[i] = (char *)malloc(sizeof(char) * (life->w + 1));
		if (!life->m[i])
		{
			free_map(life, i);
			printf("Error\n");
			exit(1); // cant use
		}
		i++;
	}

	int j = 0;
	while (j < life->h)
	{
		i = 0;
		while (i < life->w)
		{
			life->m[j][i] = ' ';
			i++;
		}
		life->m[j][i] = '\0';
		j++;
	}
}

void walking(t_life *life)
{
	char buf;
	size_t n = 1;
	bool writing = false;
	int i = 0;
	int j = 0;
	while (read(STDIN_FILENO, &buf, n) > 0)
	{
		if (buf == 'w')
		{
			if (j > 0)
				j -= 1;
		}
		else if (buf == 's')
		{
			if (j < life->h - 1)
				j += 1;
		}
		else if (buf == 'a')
		{
			if (i > 0)
				i -= 1;
		}
		else if (buf == 'd')
		{
			if (i < life->w - 1)
				i += 1;
		}
		else if (buf == 'x')
			writing = !writing;

		if (j >= 0 && j < life->h && i >= 0 && i < life->w && writing == true)
			life->m[j][i] = '0';
	}
}