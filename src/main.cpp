#include "ft_shmup.hpp"

int main()
{
    Game game;
    init_matrix(&game);
    init_ncurses(&game);
    draw_grid(&game);
    mvprintw(0, 0, "Dimensioni: %d x %d",
             game.max_win_row, 
             game.max_win_col);
    refresh();
    getch();

    endwin();
    return 0;
}