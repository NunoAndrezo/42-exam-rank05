#ifndef LIFE_HPP
#define LIFE_HPP

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_game
{
	int	width;
	int	height;
	int	iterations;
	char **map;
	char **new_map;
	bool is_new_map;
} t_game;

void init_game(t_game *game);
int grab_args(char **av, t_game *game);
int make_the_map(t_game *game);
int parse_steps(t_game *game);
void print_map(t_game *game);
int make_the_new_map(t_game *game);
int count_neighboors(t_game *game, int y, int x);
void play_game_of_life(t_game *game);
void copy_new_map_to_map(t_game *game);

#endif