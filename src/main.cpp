#include "ft_shmup.hpp"


void DrawHUD(Screen& scr, Game& game, long startTime, int playerCount, int endless);
bool storyMode(Game& game, int score);
void AddEnemies(Game& game, int score);

void	switchInput(int ch, Game *game, Screen& scr);

int ShowMenu(Screen& scr, int* endless);

unsigned long long frame_count = 0;

int main() {
	Screen scr;
	scr.init();
	int marginPlayersLine = 5;
	int endless = 1; // Default to endless mode
	// Show start menu to choose number of players
	int players = ShowMenu(scr, &endless);

	int h = scr.getHeight();
	int w = scr.getWidth();

	Game game(players, h - marginPlayersLine, w, h); // Start with selected player count

	game.start();
	while (game.isRunning())
	{
		// Get current dimvoid AddEnemies(Game& game, int score, int screenWidth, int screenHeight)ensions
		w = scr.getWidth();
		h = scr.getHeight();

		if (frame_count % (CLOCKS_PER_SEC * 10) == 0)
		{
			if (endless == 1) // Only add enemies in endless mode
				AddEnemies(game, game.getScore());
			{
				if (storyMode(game, game.getScore()) == false)
				{
					game.stop(); // Stop the game if story mode returns false (game over)
				}
			}
		} // Add new enemies every 10 seconds in endless mode 
		// Update every 60th of a second
		if (frame_count % (CLOCKS_PER_SEC / 6) == 0)
		{
			scr.clear(); // DONT PUT FUNCTIONS BACK 
			DrawHUD(scr, game, scr.getCurrentTime() / CLOCKS_PER_SEC, players, endless);
			game.showEntities();
			scr.refresh();
		}
		if (frame_count % (CLOCKS_PER_SEC * 5) == 0)
			game.addAsteroid(); // Add new asteroids every 5 seconds
		if (frame_count % (CLOCKS_PER_SEC / 3) == 0) // Handle input every 10th of a second
			game.addStar(); // Add new stars to the background every 3rd of a second
		if (frame_count % (CLOCKS_PER_SEC / 5) == 0)
			game.update(); // Update game state every 10th of a second

		frame_count++;
		switchInput(getch(), &game, scr);
	}
	return 0;
}

void DrawHUD(Screen& scr, Game& game, long startTime, int playerCount, int endless)
{
	int h = scr.getHeight();
	int w = scr.getWidth();

	// background color for HUD area
	wattron(stdscr, COLOR_PAIR(UHD_COLOR_PAIR));

	box(stdscr, 0, 0); // draw a box of height 5 at the bottom of the screen
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
	mvprintw(h - 2, w - 20, "MODE: %s", (endless == 1 ? "Endless" : "Story"));

	// controls row
	mvprintw(h - 2, 2, "Controls: A/D Move  W Shoot  Q Quit");

	wattr_off(stdscr, COLOR_PAIR(UHD_COLOR_PAIR), 0);
}

void AddEnemies(Game& game, int score)
{
	static int lastBossScore = 0;

	int level = score / 100; 

	int spawnChance = 30 + level * 10; 

	if (rand() % 100 < spawnChance)
	{
		int roll = rand() % 100;

		if (roll < 20)
			game.addAsteroid();
		else
			game.addMinion();
	}

	if (score >= lastBossScore + 1000)
	{
		game.addBoss();
		lastBossScore = score;
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

// true when the game is still running, false when it's over
bool storyMode(Game& game, int score)
{
	int maxWave = 3;
	static int currentWave = 0;
	static bool inWave = false;

	int minionToSpawn = 3 + currentWave * 2; // Increase enemies per wave
	int bossToSpawn = 1 + currentWave; // Spawn a boss every 2 waves

	// Quando non ci sono nemici => nuova wave
	if (game.getEnemyCount() == 0)
	{
		if (inWave)
		{
			for (int i = 0; i < bossToSpawn; ++i)
				game.addBoss();
			inWave = false;
			return true;
		}

		if (currentWave == maxWave)
			return false; // Game over, player wins

		// Avvia una nuova wave
		int minionToSpawn = 3 + currentWave * 2;
		for (int i = 0; i < minionToSpawn; ++i)
			game.addMinion();

		currentWave++;
		inWave = true;
	}
	return true;
}