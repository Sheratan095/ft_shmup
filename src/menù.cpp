#include "ft_shmup.hpp"

int ShowMenu(Screen& scr, int* endless)
{
    keypad(stdscr, TRUE);
    curs_set(0);

    int h = scr.getHeight();
    int w = scr.getWidth();

    const char *title = "FT_SHMUP";

    const char *modeOptions[] = {"Story Mode", "Endless Mode"};
    const int modeCount = 2;
    int modeChoice = 0;

    scr.clear();
    while (true)
    {
        mvprintw(h / 2 - 4, (w - (int)strlen(title)) / 2, "%s", title);
        mvprintw(h / 2 - 2, (w - 12) / 2, "Select Mode");

        for (int i = 0; i < modeCount; ++i)
        {
            int x = (w - (int)strlen(modeOptions[i])) / 2;
            int y = h / 2 + i;

            if (i == modeChoice)
            {
                attron(A_REVERSE);
                mvprintw(y, x, "%s", modeOptions[i]);
                attroff(A_REVERSE);
            }
            else
                mvprintw(y, x, "%s", modeOptions[i]);
        }

        mvprintw(h / 2 + 4, (w - 30) / 2, "Use Up/Down and Enter. Q to quit");
        scr.refresh();

        int ch = getch();
        if (ch == KEY_UP)
            modeChoice = (modeChoice - 1 + modeCount) % modeCount;
        else if (ch == KEY_DOWN)
            modeChoice = (modeChoice + 1) % modeCount;
        else if (ch == '\n' || ch == KEY_ENTER || ch == 10)
        {
            *endless = modeChoice; // 0 = Story, 1 = Endless
            break;
        }
        else if (ch == 'q' || ch == 'Q')
        {
            endwin();
            exit(0);
        }
    }
    const char *playerOptions[] = {"Single Player", "Two Players"};
    const int playerCount = 2;
    int playerChoice = 0;

    scr.clear();
    while (true)
    {
        mvprintw(h / 2 - 4, (w - (int)strlen(title)) / 2, "%s", title);

        mvprintw(h / 2 - 2, (w - 20) / 2,
                 "Mode: %s", (*endless == 1 ? "Endless" : "Story"));

        mvprintw(h / 2 - 1, (w - 15) / 2, "Select Players");

        for (int i = 0; i < playerCount; ++i)
        {
            int x = (w - (int)strlen(playerOptions[i])) / 2;
            int y = h / 2 + i + 1;

            if (i == playerChoice)
            {
                attron(A_REVERSE);
                mvprintw(y, x, "%s", playerOptions[i]);
                attroff(A_REVERSE);
            }
            else
                mvprintw(y, x, "%s", playerOptions[i]);
        }

        mvprintw(h / 2 + 5, (w - 30) / 2, "Use Up/Down and Enter. Q to quit");
        scr.refresh();

        int ch = getch();
        if (ch == KEY_UP)
            playerChoice = (playerChoice - 1 + playerCount) % playerCount;
        else if (ch == KEY_DOWN)
            playerChoice = (playerChoice + 1) % playerCount;
        else if (ch == '\n' || ch == KEY_ENTER || ch == 10)
            return playerChoice + 1; // 1 or 2 players
        else if (ch == 'q' || ch == 'Q')
        {
            endwin();
            exit(0);
        }
    }
}