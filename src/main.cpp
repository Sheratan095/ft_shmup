#include "ft_shmup.hpp"


void DrawHUD(Screen& scr, Game& game, long startTime, int playerCount);

void AddEnemies(Game& game, int score);

void	switchInput(int ch, Game *game, Screen& scr);

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
    game.addMinion(); // Start with one enemy
    game.addAsteroid(); // Start with one asteroid
    game.addBoss(); // Start with one boss
	while (game.isRunning())
	{
		// Get current dimvoid AddEnemies(Game& game, int score, int screenWidth, int screenHeight)ensions
        w = scr.getWidth();
        h = scr.getHeight();

        if (frame_count % (CLOCKS_PER_SEC * 10) == 0) 
            AddEnemies(game, game.getScore());
        // Update every 60th of a second
        if (frame_count % (CLOCKS_PER_SEC / 6) == 0)
        {
			scr.clear(); // DONT PUT FUNCTIONS BACK 
            DrawHUD(scr, game, scr.getCurrentTime() / CLOCKS_PER_SEC, players);
            game.showEntities();
			scr.refresh();
        }
		if (frame_count % (CLOCKS_PER_SEC / 3) == 0) // Handle input every 10th of a second
			game.addStar(); // Add new stars to the background every 3rd of a second
        if (frame_count % (CLOCKS_PER_SEC / 10) == 0)
            game.update(); // Update game state every 10th of a second

        frame_count++;
		switchInput(getch(), &game, scr);
	}
	return 0;
}

void DrawHUD(Screen& scr, Game& game, long startTime, int playerCount)
{
    int h = scr.getHeight();
    int w = scr.getWidth();

    // background color for HUD area
    wattron(stdscr, COLOR_PAIR(UHD_COLOR_PAIR));

    // separator line above HUD
    mvhline(h - 5, 0, ' ', w); // clear the row just above HUD
    mvhline(h - 4, 0, '-', w);

    // clear HUD rows before drawing (in case text from previous frame lingers)
    for (int row = h - 3; row < h; ++row)
        mvhline(row, 0, ' ', w);

    // primary stats line
    int col = 2;
    mvprintw(h - 3, col, "Score: %d", game.getScore());
    col += 15;

    if (playerCount > 1)
    {
        mvprintw(h - 3, col, "P1 HP: %d", game.getPlayerHealth(0));
        col += 15;
        mvprintw(h - 3, col, "P2 HP: %d", game.getPlayerHealth(1));
    }
    else
    {
        mvprintw(h - 3, col, "HP: %d", game.getPlayerHealth(0));
    }

    // time on right side
    mvprintw(h - 3, w - 20, "Time: %lds", startTime);

    // controls row
    mvprintw(h - 2, 2, "Controls: A/D Move  W Shoot  Q Quit");

    wattr_off(stdscr, COLOR_PAIR(UHD_COLOR_PAIR), 0);
}

void AddEnemies(Game& game, int score)
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

void switchInput(int ch, Game *game, Screen& scr)
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
        case KEY_RESIZE:
            scr.handleResize();
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

