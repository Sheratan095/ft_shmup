#include "ft_shmup.hpp"


void DrawHUD(Screen& scr, Game& game, long startTime);

void AddEnemies(Game& game, int score, int screenWidth, int screenHeight);

void	switchInput(int ch, Game *game);

int ShowMenu(Screen& scr);

unsigned long long frame_count = 0;

int main() {
	Screen scr;
	scr.init();
	int marginPlayersLine = 5;

    // Show start menu to choose number of players
    int players = ShowMenu(scr);

    int h = scr.getHeight();
	int w = scr.getWidth();

    Game game(players, h - marginPlayersLine, w, h); // Start with selected player count

    game.start();
    game.addBoss(); // Start with one enemy
	while (game.isRunning())
	{

		// Get current dimvoid AddEnemies(Game& game, int score, int screenWidth, int screenHeight)ensions
        w = scr.getWidth();
        h = scr.getHeight();

        if (frame_count % (CLOCKS_PER_SEC * 10) == 0) 
            AddEnemies(game, game.getScore(), w, h);
        // Update every 60th of a second
        if (frame_count % (CLOCKS_PER_SEC / 6) == 0)
        {
			scr.clear(); // DONT PUT FUNCTIONS BACK 
            DrawHUD(scr, game, scr.getCurrentTime() / CLOCKS_PER_SEC);
            game.showEntities(scr);
			scr.refresh();
        }
        if (frame_count % (CLOCKS_PER_SEC / 3) == 0) // Update game logic every 10th of a second
            game.update();
		if (frame_count % (CLOCKS_PER_SEC * 3) == 0) // Handle input every 10th of a second
			game.addStar(); // Add new stars to the background every 3rd of a second

        frame_count++;
		switchInput(getch(), &game);
	}
	return 0;
}

void DrawHUD(Screen& scr, Game& game, long startTime)
{
    int h = scr.getHeight();
    int w = scr.getWidth();


    int playerHealth = game.getPlayerHealth(0);

	wattron(stdscr, COLOR_PAIR(UHD_COLOR_PAIR));
    mvhline(h - 4, 1, '-', w);  // top border of HUD
	box(stdscr, 0, 0); // Draw border around the screen
	mvprintw(h - 3, 2, "|"); // left border of HUD
    mvprintw(h - 3, 2, "Score: %d", game.getScore());
    mvprintw(h - 3, w / 3, "Health: %d", playerHealth);
	mvprintw(h - 3, (2 * w) / 3, "Time: %lds ", startTime);

    mvprintw(h - 2, 2, "Controls: A/D Move  W Shoot  Q Quit");
	wattroff(stdscr, A_NORMAL);
}

void AddEnemies(Game& game, int score, int screenWidth, int screenHeight)
{
    int difficultyLevel = score / 100; // Increase difficulty every 100 points
    // Add a new enemy every 100 points

    while (difficultyLevel > 0) // 10% chance to add an enemy each frame, scaled by difficulty
    {
        // Randomly decide to add either an AEnemy or an Asteroid
        int divisor = std::max(1, 10 - difficultyLevel); // Ensure divisor is never 0
        if (rand() % divisor == 0)
            game.addMinion(); // ADD ENEMY HERE
        else
            game.addAsteroid(); // ADD ASTEROID HERE
        difficultyLevel--;
    }
}

void switchInput(int ch, Game *game)
{

    switch (ch)
    {
        // Player 0
        case 'a':
        case 'A':
            game->playerMove(0, -1);
            break;

        case 'd':
        case 'D':
            game->playerMove(0, 1);
            break;

        case 'w':
        case 'W':
            game->playerShoot(0);
            break;

        // Player 1
        case KEY_LEFT:
            game->playerMove(1, -1);
            break;

        case KEY_RIGHT:
            game->playerMove(1, 1);
            break;
        case KEY_UP:
            game->playerShoot(1);
            break;

        // Quit
        case 'q':
        case 'Q':
            game->stop(); // Stop the game
            break;

        default:
            break;
    }
}

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