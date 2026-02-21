#include "ft_shmup.hpp"



void	init_matrix(Game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			game->grid[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	init_ncurses(Game *game)
{
	initscr();
	curs_set(INVISIBLE_CURSOR);
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	//setup_colors();
	getmaxyx(stdscr, game->max_win_row, game->max_win_col);

}

void	draw_grid(Game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	value;

	clear();
	y = 4;
	i = 0;
	while (i < GRID_SIZE)
	{
		mvprintw(y, 2, "|");
		j = 0;
		while (j < GRID_SIZE)
		{
			x = 3 + (j * 9);
			value = game->grid[i][j];
			if (value == 0)
				mvprintw(y, x, "        ");
			mvprintw(y, 11 + (j * 9), "|");
			j++;
		}
		y++;
		if (i < 3)
		{
			mvprintw(y, 2, "+--------+--------+--------+--------+");
			y++;
		}
		i++;
	}
	mvprintw(y, 2, "+--------+--------+--------+--------+");
	refresh();
}