#include "ft_shmup.hpp"

int ShowMenu(Screen& scr)
{
    int h = scr.getHeight();
    int w = scr.getWidth();

    const char *title = "FT_SHMUP";
    const char *options[] = {"Single Player", "Two Players"};
    const int optCount = 2;
    int choice = 0;

    keypad(stdscr, TRUE);
    curs_set(0);
    int prev_choice = -1;
    bool first_draw = true;

    while (true)
    {
        if (first_draw || choice != prev_choice)
        {
            scr.clear();
            mvprintw(h / 2 - 3, (w - (int)strlen(title)) / 2, "%s", title);
            for (int i = 0; i < optCount; ++i)
            {
                int x = (w - (int)strlen(options[i])) / 2;
                int y = h / 2 - 1 + i;
                if (i == choice)
                {
                    attron(A_REVERSE);
                    mvprintw(y, x, "%s", options[i]);
                    attroff(A_REVERSE);
                }
                else
                {
                    mvprintw(y, x, "%s", options[i]);
                }
            }
            mvprintw(h / 2 + 3, (w - 30) / 2, "Use Up/Down and Enter to select. Q to quit");
            scr.refresh();
            prev_choice = choice;
            first_draw = false;
        }

        int ch = getch();
        if (ch == KEY_UP)
            choice = (choice - 1 + optCount) % optCount;
        else if (ch == KEY_DOWN)
            choice = (choice + 1) % optCount;
        else if (ch == '\n' || ch == KEY_ENTER || ch == 10)
            return choice + 1; // return 1 or 2
        else if (ch == 'q' || ch == 'Q')
        {
            endwin();
            exit(0);
        }
        // Ignore other keys (including number keys)
    }
}