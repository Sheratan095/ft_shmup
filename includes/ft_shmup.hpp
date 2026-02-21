#ifndef FT_SHMUP_HPP
#define FT_SHMUP_HPP

#include <iostream>
#include <string>

#include "AEntity.hpp"
#include "Screen.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include <iostream>
#include <string>
#include <ncurses.h>

#define INVISIBLE_CURSOR 0
#define GRID_SIZE	4

enum class Move
{
    Default,
    Left,
    Right
};

struct Game {
    int max_win_row;
    int max_win_col;
	int	grid[GRID_SIZE][GRID_SIZE];
};

void	init_ncurses(Game *game);
void	init_matrix(Game *game);
void	draw_grid(Game *game);
int     handle_input(Game *game);

#endif