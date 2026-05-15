#ifndef BSQ_H
#define BSQ_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

/*  
 - The number of lines on the map;
 - The "empty" character;
 - The "obstacle" character;
 - The "full" character. 
*/
typedef struct s_bsq
{
	int		n_lines;
	char	empty;
	char	obstacle;
	char	full;

	char	**map;

	int		x_start;
	int		y_start;
	int		biggest;
} t_bsq;

#endif