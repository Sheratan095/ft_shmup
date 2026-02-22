#include "ft_shmup.hpp"


void DrawHUD(Screen& scr, const Game& game, int startTime);

void AddEnemies(Game& game, int score, int screenWidth, int screenHeight);

void	switchInput(int ch, Game *game, bool *running);

unsigned long long frame_count = 0;

int main() {
	Screen scr;
	scr.init();
	int marginPlayersLine = 5;

		
    int h = scr.getHeight();
	int w = scr.getWidth();

	Game game(1, h - marginPlayersLine, w, h); // Start with 1 player, screen width, and player starting Y position

	bool running = true;
    game.start();
    game.addMinion(); // Start with one enemy
	while (running)
	{

		// Get current dimvoid AddEnemies(Game& game, int score, int screenWidth, int screenHeight)ensions
        w = scr.getWidth();
        h = scr.getHeight();

        if (frame_count % (CLOCKS_PER_SEC) == 0) // Add enemies every half second
            AddEnemies(game, game.getScore(), w, h);

        // Update every 60th of a second
        if (frame_count % (CLOCKS_PER_SEC / 60) == 0)
        {
            scr.clear(); // DONT PUT FUNCTIONS BACK 
            DrawHUD(scr, game, scr.getCurrentTime() / CLOCKS_PER_SEC);
            game.showEntities(scr);
        }
        if (frame_count % (CLOCKS_PER_SEC) == 0) // Update game logic every 10th of a second
            game.update();

        frame_count++;
		switchInput(getch(), &game, &running);
	}
	return 0;
}

void DrawHUD(Screen& scr, const Game& game, int startTime)
{
	
    int h = scr.getHeight();
    int w = scr.getWidth();

    int playerHealth = game.getPlayerHealth(0);

	wattron(stdscr, COLOR_PAIR(UHD_COLOR_PAIR));

    mvhline(h - 4, 0, '-', w);  // top border of HUD
    mvprintw(h - 3, 2, "Score: %d", game.getScore());
    mvprintw(h - 3, w / 3, "Health: %d", playerHealth);
	mvprintw(h - 3, (2 * w) / 3, "Time: %lds", (long)(scr.getCurrentTime() / CLOCKS_PER_SEC));

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

void	switchInput(int ch, Game *game, bool *running)
{
	switch (ch)
	{
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

		case KEY_LEFT:
			game->playerMove(1, -1);
			break;

		case KEY_RIGHT:
			game->playerMove(1, 1);
			break;

		case KEY_UP:
			game->playerShoot(1);
			break;

		case 'q':
		case 'Q':
            *running = false;
			break;

		default:
			break;
	}
}