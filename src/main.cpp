#include "ft_shmup.hpp"

void AddEnemies(Game& game, int score, int screenWidth, int screenHeight);

void	switchInput(int ch, Game *game);

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
    //game.addEnemy(); // Start with one enemy
	while (running)
	{

		// Get current dimvoid AddEnemies(Game& game, int score, int screenWidth, int screenHeight)ensions
        w = scr.getWidth();
        h = scr.getHeight();

        AddEnemies(game, game.getScore(), w, h);

        // Update every 60th of a second
        if (frame_count % (CLOCKS_PER_SEC / 60) == 0)
        {
            scr.clear();
            game.showEntities(scr);
            game.update();
        }

        frame_count++;
		switchInput(getch(), &game);
	}


    scr.end();
	return 0;
}



void AddEnemies(Game& game, int score, int screenWidth, int screenHeight)
{
    int difficultyLevel = 1000; // Increase difficulty every 100 points
    // Add a new enemy every 100 points

    while (difficultyLevel > 0) // 10% chance to add an enemy each frame, scaled by difficulty
    {
        // Randomly decide to add either an AEnemy or an Asteroid
        if (rand() % (10 - difficultyLevel) == 0)
            cout << "Adding an enemy!" << endl; // ADD ENEMY HERE
        else
            cout << "Adding an asteroid!" << endl; // ADD ASTEROID HERE
        difficultyLevel--;
    }
}

void	switchInput(int ch, Game *game)
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
			exit(0);
			break;

		default:
			break;
	}
}