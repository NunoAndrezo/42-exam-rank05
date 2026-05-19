#ifndef LIFE01_H
#define LIFE01_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct s_life
{
	int w;
	int h;
	int iter;
	char **m;
	char **new_map;
} t_life;

void init_s(t_life *life);
void grab_args(t_life *life, char **s);
void start_map(t_life *life);
void walking(t_life *life);
void create_new_map(t_life *life);
void play_game(t_life *life);
void cp_map(t_life *life);
int check_neighbour(int y, int x, t_life *life);
void create_new_map(t_life *life);
void free_map(t_life *life, int j);
void free_map_new_map(t_life *life, int j);

#endif